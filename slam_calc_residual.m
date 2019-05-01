% Calculate IMU preintegration between poses in the sliding window
residual = [];
r_R = zeros(window_size-1, 3); % attitude error preintegration between poses
r_V = zeros(window_size-1, 3); % velocity error preintegration between poses
r_P = zeros(window_size-1, 3); % position error preintegration between poses

for vertice=1:window_size-1
    imu_sample_from = ((window_range_from - 1) + (vertice - 1)) * kf_interval_imu + 1;
    imu_sample_to = ((window_range_from - 1) + vertice) * kf_interval_imu;
    
    deltaR = eye(3);
    deltaV = zeros(3,1);
    deltaP = zeros(3,1);
    
    for i=imu_sample_from:imu_sample_to
        % DeltaR
        omega = gyro.Data(i,:);
        omega_an = norm(omega); % rotation angle
        omega_ax = omega/omega_an*imu_sampling_time;
        deltaRik = axang2rotm([omega_ax omega_an]);
        % DeltaV
        vel = accel.Data(i,:);
        deltaVelik = deltaR*(accel.Data(i,:))'*imu_sampling_time;
        deltaV = deltaV + deltaVelik;
        % DeltaP
        deltaPik = 3/2 * deltaR * (accel.Data(i,:))' * (imu_sampling_time.^2);
        deltaP = deltaP + deltaPik;
        % After calculating DeltaV and DeltaP, it is possible to update
        % deltaR
        deltaR = deltaR * deltaRik;
    end
    
    att_axang = rotm2axang(deltaR);
    att = att_axang(4)*(att_axang(1:3));
    r_R(vertice,:) = att;
    r_V(vertice,:) = deltaV;
    r_P(vertice,:) = deltaP;
    
end

% Calculate residual vector
for i=1:(window_size-1)
    % Residual of attitude error between keyframes
    dR = Ro(:,:,i)'*Ro(:,:,i+1);
    dr = rotm2axang(dR);
    dr_an = dr(4);
    dr_ax = dr(1:3);
    dr = dr_ax * dr_an; % log of attitude difference between keyframe i and i+1
    ddr = dr - r_R(i,:); 
    residual=[residual ddr];
    % Residual of velocity error between keyframes
    dv = Ro(:,:,i)' * (Vo(i+1,:)-Vo(i,:)-[0 0 9.81]*imu_sampling_time)';
    ddv = dv' - r_V(i,:);
    residual=[residual ddv];
    % Residual of position error between keyframes
    dp = Ro(:,:,i)' * (Po(i+1,:)-Po(i,:)-Vo(i,:)*imu_sampling_time-0.5*[0 0 9.81]*imu_sampling_time.^2)';
    ddp = dp' - r_P(i,:);
    residual=[residual ddp];
    % Residual of photometric error of keyframes
    xyzl = Ro(:,:,i)*(Lo - Po(i,:))';
    lmip = focal_length*[xyzl(1)/xyzl(3) xyzl(2)/xyzl(3)]; % projection to image plan eq, using focal length 0.024m
    % lmip is predicted location of landmark in the image plane
    cam_sample = ((window_range_from - 1) + (i - 1)) * kf_interval_cam + 1; % the keyframe corresponds to the camera frame of cam_sample
    lmip_m = feature.Data(cam_sample,:); % measurement of landmark at the currennt keyframe time
    ephoto = lmip - lmip_m;
    residual=[residual ephoto];
end

% Residual of photometric error of the last keyframe
i = 5;
xyzl = Ro(:,:,i)*(Lo - Po(i,:))';
lmip = focal_length*[xyzl(1)/xyzl(3) xyzl(2)/xyzl(3)]; % projection to image plan eq, using focal length 0.024m
% lmip is predicted location of landmark in the image plane
cam_sample = ((window_range_from - 1) + (i - 1)) * kf_interval_cam + 1; % the keyframe corresponds to the camera frame of cam_sample
lmip_m = feature.Data(cam_sample,:); % measurement of landmark at the currennt keyframe time
ephoto = lmip - lmip_m;
residual=[residual ephoto];