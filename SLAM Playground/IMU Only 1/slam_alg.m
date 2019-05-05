clear all;
clc;

% Load data from simulation
load('slamdatai');

% Resample the IMU and camera data
run('slam_sanitizer');

% Parameters
kf_interval_imu = 50; % 20 IMU samples for 1 keyframe
kf_interval_cam = 50; % 20 camera samples for 1 keyframe
window_size = 5; % sliding window length
imu_sampling_time = 0.02; % sampling time of IMU data
focal_length = 0.024; % focal length is 24mm
residual_vector_length = window_size * 9 + 0; % which is 48, in case window_size = 5
gn_iterations = 120; % num of iterations per Gauss-Newton loop

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
Vo = zeros(window_size,3); % velocity of keyframes
Lo = zeros(1,3); % position of landmark

% Residual calculation
% Residual vector contains log(R1'R2) R1'(v2-v1-gdt)
% R1'(p2-p1-v1dt-1/2gdt^2) ... e_photo (photometric error)

% Parameters
residual = []; % residual
J = []; % Jacobian matrix
bstar = []; % Prior information from Schur Marginalization
Hstar = []; % "
cost_fn = [];

% Begin window sliding
for iw=1:window_range_to
    window_range_from = window_range_from + 1;
    % Begin Gauss-Newton loop and solve
    for is=1:gn_iterations
        
        run('slam_calc_residual');
        run('slam_calc_jacobian');
        
        % Calculate current cost
        cost_fn = [cost_fn residual*residual'];
        
        H = J'*J+0.1*eye(size(J,2)); % No marginalization, Levenberg-Marquadt
        b = -J'*residual';
        delta = pinv(H)*b;
        % Parameter Update
        for j=1:window_size
           offset_from = (j-1)*9+1; % Begin of the phi_j
           Ri_update_com = delta(offset_from:offset_from+2);
           % Update phi_j
           Ri_update_an = norm(Ri_update_com);
           Ri_update_ax = Ri_update_com'./Ri_update_an;
           Ri_update_R = axang2rotm([Ri_update_ax Ri_update_an]);
           Ro(:,:,j) = Ro(:,:,j)*Ri_update_R;
           % Update v_j
           Vi_update_com = delta(offset_from+3:offset_from+5);
           Vo(j,:) = Vo(j,:) + Vi_update_com';
           % Update p_j
           Pi_update_com = delta(offset_from+6:offset_from+8);
           Pi_update = (Ro(:,:,j)*Pi_update_com)';
           Po(j,:) = Po(j,:) + Pi_update;
        end
        % Update L
%         Lo_update = delta(window_size*9+1:window_size*9+3);
%         Lo = Lo + Lo_update';
    end
end

% Open a new figure to indicate cost function
figure;
plot(cost_fn);