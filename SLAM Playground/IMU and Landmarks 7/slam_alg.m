clear all;
clc;

% Load data from simulation
load('slamdata5');

% Resample the IMU and camera data
run('slam_sanitizer');

% Parameters
kf_interval_imu = 30; % 20 IMU samples for 1 keyframe
kf_interval_cam = 30; % 20 camera samples for 1 keyframe
window_size = 12; % sliding window length
imu_sampling_time = 0.02; % sampling time of IMU data
focal_length = 0.024; % focal length is 24mm
num_of_landmarks = 5;
total_state_size = window_size * 9 + 3 * num_of_landmarks; % 3 is the number of observing landmarks, THIS IS THE STATE SIZE!
residual_vector_length = (window_size - 1) * 9 + window_size * num_of_landmarks * 2;

gn_iterations = 500; % num of iterations per Gauss-Newton loop

% Initialize variables
r_R = zeros(window_size-1, 3); % attitude error preintegration between poses
r_V = zeros(window_size-1, 3); % velocity error preintegration between poses
r_P = zeros(window_size-1, 3); % position error preintegration between poses

window_range_from = 0; % beginning position of the window, which is
% equivalent to how many keyframes have been marginalised + 1
% note that only residuals depend on window_range_from while Jacobians are
% not
window_range_to = 1;

% Optimization variables
Ro = zeros(3,3,window_size);
Po = zeros(window_size,3);
for i=1:(window_size)
    Ro(:,:,i) = eye(3); % attitude of keyframes
    Po(i,:) = [0 0 -4]; % position of keyframes
end
Po(1,:) = [0 0 -4];
Vo = zeros(window_size,3); % velocity of keyframes
Lo = zeros(num_of_landmarks,3); % position of landmark

absolute_optimization_flag = 0; % if this flag is set to 1, optimization will start from absolute zero error

Rt = [];
Vt = [];
Pt = [];
for q=1:window_size
    true_quant_from = ((window_range_from + 1 - 1) + (q - 1)) * kf_interval_imu + 1;
    Rt(:,:,q) = true_att.Data(:,:,true_quant_from);
    Vt(q,:) = true_v.Data(true_quant_from,:);
    Pt(q,:) = true_pos.Data(true_quant_from,:);
end
Lt = [0 0 0;
      1 0 0;
      0 -1 0;
      2 2 0;
      1.2 2.1 0];

if (absolute_optimization_flag==1)
    Po = Pt; 
    Ro = Rt;
    Vo = Vt;
    Lo = [1 1 0;
      1 1 0;
      1 1 0];
end

% Parameters
residual = []; % residual
J = []; % Jacobian matrix
bstar = []; % Prior information from Schur Marginalization
Hstar = []; % "
cost_fn = [];

% Weight initialization
WM = eye(residual_vector_length-9);

% Begin window sliding
for iw=1:window_range_to
    window_range_from = window_range_from + 1;
    position_cost = [];
    % Begin Gauss-Newton loop and solve
    for is=1:gn_iterations
        
        run('slam_calc_residual');
        run('slam_calc_jacobian');
        
        % Calculate current cost
        cost_fn = [cost_fn residualt*residualt'];
        
%         if (is==1)
%             residualt = zeros(1,96);
%             residualt(1)=0.01;
%         end
        
        J = J(:,10:size(J,2));
        
        
        %H = J'*WM*J+Jp'*Jp+0.1*eye(size(J,2)); % No marginalization, Levenberg-Marquadt
        %b = -J'*WM*residualt' - Jp'*residualp';
        H = J'*WM*J+10*eye(size(J,2)); % No marginalization, Levenberg-Marquadt
        b = -J'*WM*residualt';
        Hstar = [H Jl';
            Jl zeros(num_of_landmarks)];
        bstar = [b; zeros(num_of_landmarks,1)];
        
        if(rank(J')<total_state_size-9)
            fprintf('Jacobian matrix is rank deficient (%d) at iteration %d \n', [rank(J') is]);
            fprintf('Total residual is: %f \n', residualt*residualt');
        end
        if(det(H)<0.005)
            fprintf('Hessian matrix is near rank-deficient at iteration %d \n', is);
        end
        % triangle = inv(Hstar)*bstar;
        % delta = triangle(1:total_state_size-9);
        delta = inv(H)*b;
        % Parameter Update
        for j=2:window_size
           offset_from = (j-1-1)*9+1; % Begin of the phi_j
           % Update v_j
           Vi_update_com = delta(offset_from+3:offset_from+5);
           if (j~=0)
            Vo(j,:) = Vo(j,:) + Vi_update_com';
           end
           % Update p_j
           Pi_update_com = delta(offset_from+6:offset_from+8);
           Pi_update = (Ro(:,:,j)*Pi_update_com)';
           if (j~=0)
               Po(j,:) = Po(j,:) + Pi_update;
           end
           % Update phi_j
           Ri_update_com = delta(offset_from:offset_from+2);
           Ri_update_an = norm(Ri_update_com);
           if (Ri_update_an<5e-4)
               Ri_update_ax = [1 0 0];
               Ri_update_an = 0;
           else
               Ri_update_ax = Ri_update_com'./Ri_update_an;
           end
           Ri_update_R = axang2rotm([Ri_update_ax Ri_update_an]);
           if (j~=0)
               Ro(:,:,j) = Ro(:,:,j)*Ri_update_R;
           end
        end
        % Update L
         for lmk=1:num_of_landmarks
            Lo_update = delta((window_size-1)*9+(lmk-1)*3+1:(window_size-1)*9+lmk*3);
            Lo_update(3) = 0;
            Lo(lmk,:)=Lo(lmk,:) + Lo_update';
        end
    end
end

% Open a new figure to indicate cost function
figure;
plot(cost_fn);