Ro = true_att.Data;
Vo = true_v.Data;
Po = true_pos.Data;

for i=1:(window_size-1)
    % Residual of attitude error between keyframes
    fprintf('Key frame %d \n', i);
    dR = Ro(:,:,i)'*Ro(:,:,i+1);
    dr = rotm2axang(dR);
    dr_an = dr(4);
    dr_ax = dr(1:3);
    dr = dr_ax * dr_an; % log of attitude difference between keyframe i and i+1
    disp(dr);
    % ddr = dr - r_R(i,:); 
    % residual=[residual ddr];
    % Residual of velocity error between keyframes
    dv = Ro(:,:,i)' * (Vo(i+1,:)-Vo(i,:)-[0 0 9.81]*imu_sampling_time*kf_interval_imu)';
    disp(dv);
    % ddv = dv' - r_V(i,:);
    % residual=[residual ddv];
    % Residual of position error between keyframes
    dp = Ro(:,:,i)' * (Po(i+1,:)-Po(i,:)-Vo(i,:)*imu_sampling_time*kf_interval_imu-0.5*[0 0 9.81]*(imu_sampling_time*kf_interval_imu).^2)';
    disp(dp);
    % ddp = dp' - r_P(i,:);
    % residual=[residual ddp];
end