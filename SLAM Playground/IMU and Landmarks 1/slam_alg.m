clear all;
clc;

% Load data from simulation
load('slamdata4');

% Resample the IMU and camera data
run('slam_sanitizer');

% Parameters
kf_interval_imu = 50; % 20 IMU samples for 1 keyframe
kf_interval_cam = 50; % 20 camera samples for 1 keyframe
window_size = 20; % sliding window length
imu_sampling_time = 0.02; % sampling time of IMU data
focal_length = 0.024; % focal length is 24mm
num_of_landmarks = 3;
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
    Po(i,:) = [3 7 -2]; % position of keyframes
end
Vo = zeros(window_size,3); % velocity of keyframes
Lo = zeros(num_of_landmarks,3); % position of landmark

% Parameters
residual = []; % residual
J = []; % Jacobian matrix
bstar = []; % Prior information from Schur Marginalization
Hstar = []; % "
cost_fn = [];

% Weight initialization
WM = eye(residual_vector_length);

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
        
        H = J'*WM*J+Jp'*Jp+0.1*eye(size(J,2)); % No marginalization, Levenberg-Marquadt
        b = -J'*WM*residualt' - Jp'*residualp';
        if(mod(is,10)==0)
            % disp(residualt);
        end
        delta = pinv(H)*b;
        % Parameter Update
        for j=1:window_size
           offset_from = (j-1)*9+1; % Begin of the phi_j
           % Update v_j
           Vi_update_com = delta(offset_from+3:offset_from+5);
           Vo(j,:) = Vo(j,:) + Vi_update_com';
           % Update p_j
           Pi_update_com = delta(offset_from+6:offset_from+8);
           Pi_update = (Ro(:,:,j)*Pi_update_com)';
           Po(j,:) = Po(j,:) + Pi_update;
           % Update phi_j
           Ri_update_com = delta(offset_from:offset_from+2);
           Ri_update_an = norm(Ri_update_com);
           if (Ri_update_an<0.005)
               Ri_update_ax = [1 0 0];
           else
               Ri_update_ax = Ri_update_com'./Ri_update_an;
           end
           Ri_update_R = axang2rotm([Ri_update_ax Ri_update_an]);
           if (j~=1)
               Ro(:,:,j) = Ro(:,:,j)*Ri_update_R;
           end
        end
        % Update L
         for lmk=1:num_of_landmarks
            Lo_update = delta(window_size*9+(lmk-1)*3+1:window_size*9+lmk*3);
            Lo_update(3) = 0;
            Lo(lmk,:)=Lo(lmk,:) + Lo_update';
        end
    end
end

% Open a new figure to indicate cost function
figure;
plot(cost_fn);