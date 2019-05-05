% Jacobian is of deltaR, deltaV, deltaP, deltaePhoto and repeat
J = [];
for i=1:(window_size-1)
    % Jacobian for deltaR12 <--
    rowOffset = (i-1)*9+1; % position to insert the Jacobian
    rowJ = [];
    for j=1:(rowOffset-1)
        rowJ = [rowJ zeros(3,1)];
    end
    % rcf = (i-1)*9+1; % not correct, must use the optimization values
    % rct = (i-1)*9+3;
    % rcv = residual(rcf:rct); % the residual component corresponds to deltaR12
    rcv = rotm2axang(Ro(:,:,i)'*Ro(:,:,i+1));
    rcv = rcv(1:3)*rcv(4);
    if (norm(rcv)<0.005)
        JRi = eye(3);
    else
        JRi = eye(3) + 1/2*hat(rcv) + (1/norm(rcv)^2 + (1+cos(norm(rcv)))/(2*norm(rcv)*sin(norm(rcv))))*hat(rcv)*hat(rcv);
    end
    JR = -JRi*Ro(:,:,i+1)'*Ro(:,:,i);
    rowJ = [rowJ JR]; % Jacobian wrt R1
    rowJ = [rowJ zeros(3)]; % Jacobian wrt v1
    rowJ = [rowJ zeros(3)]; % Jacobian wrt p1
    % Jacobian for deltaR12 by phi2
    % rcf2 = (i-1)*9+10;
    % rct2 = (i-1)*9+12;
    % rcv2 = residual(rcf2:rct2); % the residual component corresponds to deltaR12
    rcv2 = rotm2axang(Ro(:,:,i)'*Ro(:,:,i+1));
    rcv2 = rcv2(1:3)*rcv2(4);
    if (norm(rcv2)<0.005)
        JRi2 = eye(3);
    else
        JRi2 = eye(3) + 1/2*hat(rcv2) + (1/norm(rcv2)^2 + (1+cos(norm(rcv2)))/(2*norm(rcv2)*sin(norm(rcv2))))*hat(rcv2)*hat(rcv2);
    end
    rowJ = [rowJ JRi2];
    % For the rest of the residuals, put in 0
    remaining_residual_length = total_state_size - length(rowJ);
    for j=1:remaining_residual_length
        rowJ = [rowJ zeros(3,1)];
    end
    J = [J; rowJ];
    % Jacobian for deltaV12 <--
    rowJ = [];
    for j=1:(rowOffset-1)
        rowJ = [rowJ zeros(3,1)];
    end
    Jvr = hat(Ro(:,:,i)'*(Vo(i+1,:)'-Vo(i,:)'-[0 0 9.81]'*imu_sampling_time*kf_interval_imu)); % Jacobian wrt phi1
    rowJ = [rowJ Jvr];
    Jvv = -Ro(:,:,i)';
    rowJ = [rowJ, Jvv]; % Jacobian wrt v1
    rowJ = [rowJ, zeros(3)]; % Jacobian wrt p1
    rowJ = [rowJ, zeros(3)]; % Jacobian wrt phi2
    rowJ = [rowJ, Ro(:,:,i)']; % Jacobin wrt v2
    % For the rest of the residuals, put in 0
    remaining_residual_length = total_state_size - length(rowJ);
    for j=1:remaining_residual_length
        rowJ = [rowJ zeros(3,1)];
    end
    J = [J; rowJ];
    % Jacobian for deltaP12 <--
    rowJ = [];
    for j=1:(rowOffset-1)
        rowJ = [rowJ zeros(3,1)];
    end
    Jpr = hat(Ro(:,:,i)'*(Po(i+1,:)-Po(i,:)-Vo(i,:)*imu_sampling_time*kf_interval_imu-0.5*[0 0 9.81]*((imu_sampling_time*kf_interval_imu).^2))'); % Jacobian wrt phi1
    rowJ = [rowJ Jpr];
    Jvv = -Ro(:,:,i)'*imu_sampling_time*kf_interval_imu; % Jacobian wrt v1
    rowJ = [rowJ Jvv]; 
    Jvp = -eye(3); % Jacobian wrt p1
    rowJ = [rowJ Jvp];
    rowJ = [rowJ zeros(3) zeros(3)]; % Rij wrt phij and vj
    rowJ = [rowJ Ro(:,:,i)'*Ro(:,:,i+1)]; % Jacobian wrt p2
    % For the rest of the residuals, put in 0
    remaining_residual_length = total_state_size - length(rowJ);
    for j=1:remaining_residual_length
        rowJ = [rowJ zeros(3,1)];
    end
    J = [J; rowJ];
    % Jacobian for photometric error of keyframe i (missing one final
    % keyframe, which will be addressed separately later) <--
    for lmi=1:num_of_landmarks
        rowJ = [];
        for j=1:(rowOffset-1)
            rowJ = [rowJ zeros(2,1)];
        end
        % Jacobian of photometric error wrt phi1
        Gamma = Ro(:,:,i)' * (Lo(lmi,:) - Po(i,:))';
        xp = Gamma(1); yp = Gamma(2); zp = Gamma(3);
        dGdP = hat(Ro(:,:,i)' * (Lo(lmi,:) - Po(i,:))');
        addToRowJ = focal_length * [(dGdP(1,1)*zp - dGdP(3,1)*xp)/zp^2 (dGdP(1,2)*zp - dGdP(3,2)*xp)/zp^2 (dGdP(1,3)*zp - dGdP(3,3)*xp)/zp^2;
            (dGdP(2,1)*zp - dGdP(3,1)*yp)/zp^2 (dGdP(2,2)*zp - dGdP(3,2)*yp)/zp^2 (dGdP(2,3)*zp - dGdP(3,3)*yp)/zp^2];
        rowJ = [rowJ addToRowJ];
        % Jacobian of photometric error wrt v1
        rowJ = [rowJ zeros(2,3)];
        % Jacobian of photometric error wrt p1
        dGdPos = -eye(3);
        addToRowJ = focal_length * [(dGdPos(1,1)*zp - dGdPos(3,1)*xp)/zp^2 (dGdPos(1,2)*zp - dGdPos(3,2)*xp)/zp^2 (dGdPos(1,3)*zp - dGdPos(3,3)*xp)/zp^2;
            (dGdPos(2,1)*zp - dGdPos(3,1)*yp)/zp^2 (dGdPos(2,2)*zp - dGdPos(3,2)*yp)/zp^2 (dGdPos(2,3)*zp - dGdPos(3,3)*yp)/zp^2];
        rowJ = [rowJ addToRowJ];
        % Jacobian of photometric error wrt Lo (landmark position)
        % First, fill in all intermediate columns with zero
        for j=(length(rowJ)+1):(total_state_size-(num_of_landmarks-lmi+1)*3)
            rowJ = [rowJ zeros(2,1)];
        end
        % Jacobian wrt landmark position
        dGdPos = Ro(:,:,i)';
        addToRowJ = focal_length * [(dGdPos(1,1)*zp - dGdPos(3,1)*xp)/zp^2 (dGdPos(1,2)*zp - dGdPos(3,2)*xp)/zp^2 (dGdPos(1,3)*zp - dGdPos(3,3)*xp)/zp^2;
            (dGdPos(2,1)*zp - dGdPos(3,1)*yp)/zp^2 (dGdPos(2,2)*zp - dGdPos(3,2)*yp)/zp^2 (dGdPos(2,3)*zp - dGdPos(3,3)*yp)/zp^2];
        rowJ = [rowJ addToRowJ];
        for j=(length(rowJ)+1):(total_state_size)
            rowJ = [rowJ zeros(2,1)];
        end
        % J = [J; rowJ];
    end
end

% Jacobian for photometric error of keyframe i (for the last keyframe) <--
i = window_size;
% Jacobian for photometric error of keyframe i (missing one final
% keyframe, which will be addressed separately later) <--
for lmi=1:num_of_landmarks
    rowJ = [];
    for j=1:(rowOffset-1)
        rowJ = [rowJ zeros(2,1)];
    end
    % Jacobian of photometric error wrt phi1
    Gamma = Ro(:,:,i)' * (Lo(lmi,:) - Po(i,:))';
    xp = Gamma(1); yp = Gamma(2); zp = Gamma(3);
    dGdP = hat(Ro(:,:,i)' * (Lo(lmi,:) - Po(i,:))');
    addToRowJ = focal_length * [(dGdP(1,1)*zp - dGdP(3,1)*xp)/zp^2 (dGdP(1,2)*zp - dGdP(3,2)*xp)/zp^2 (dGdP(1,3)*zp - dGdP(3,3)*xp)/zp^2;
        (dGdP(2,1)*zp - dGdP(3,1)*yp)/zp^2 (dGdP(2,2)*zp - dGdP(3,2)*yp)/zp^2 (dGdP(2,3)*zp - dGdP(3,3)*yp)/zp^2];
    rowJ = [rowJ addToRowJ];
    % Jacobian of photometric error wrt v1
    rowJ = [rowJ zeros(2,3)];
    % Jacobian of photometric error wrt p1
    dGdPos = -eye(3);
    addToRowJ = focal_length * [(dGdPos(1,1)*zp - dGdPos(3,1)*xp)/zp^2 (dGdPos(1,2)*zp - dGdPos(3,2)*xp)/zp^2 (dGdPos(1,3)*zp - dGdPos(3,3)*xp)/zp^2;
        (dGdPos(2,1)*zp - dGdPos(3,1)*yp)/zp^2 (dGdPos(2,2)*zp - dGdPos(3,2)*yp)/zp^2 (dGdPos(2,3)*zp - dGdPos(3,3)*yp)/zp^2];
    rowJ = [rowJ addToRowJ];
    % Jacobian of photometric error wrt Lo (landmark position)
    % First, fill in all intermediate columns with zero
    for j=(length(rowJ)+1):(total_state_size-(num_of_landmarks-lmi+1)*3)
        rowJ = [rowJ zeros(2,1)];
    end
    % Jacobian wrt landmark position
    dGdPos = Ro(:,:,i)';
    addToRowJ = focal_length * [(dGdPos(1,1)*zp - dGdPos(3,1)*xp)/zp^2 (dGdPos(1,2)*zp - dGdPos(3,2)*xp)/zp^2 (dGdPos(1,3)*zp - dGdPos(3,3)*xp)/zp^2;
        (dGdPos(2,1)*zp - dGdPos(3,1)*yp)/zp^2 (dGdPos(2,2)*zp - dGdPos(3,2)*yp)/zp^2 (dGdPos(2,3)*zp - dGdPos(3,3)*yp)/zp^2];
    rowJ = [rowJ addToRowJ];
    for j=(length(rowJ)+1):(total_state_size)
        rowJ = [rowJ zeros(2,1)];
    end
    % J = [J; rowJ];
end

% Jacobian for the Prior
Jp = [];
rowJ = [];
% Jacobian of attitude error residual
rcv = rotm2axang(Ro(:,:,1)'*Rt(:,:,1));
rcv = rcv(1:3)*rcv(4);
if (norm(rcv)<0.005)
    JRi = eye(3);
else
    JRi = eye(3) + 1/2*hat(rcv) + (1/norm(rcv)^2 + (1+cos(norm(rcv)))/(2*norm(rcv)*sin(norm(rcv))))*hat(rcv)*hat(rcv);
end
JR = -JRi*Rt(:,:,1)'*Ro(:,:,1);
rowJ = [rowJ JR]; % Jacobian wrt R1
for ww=length(rowJ)+1:total_state_size
    rowJ = [rowJ zeros(3,1)];
end
Jp = [Jp; rowJ];
% Jacobian of velocity error residual
rowJ = [];
rowJ = [rowJ zeros(3)]; % Jacobian wrt phi1
rowJ = [rowJ eye(3)]; % Jacobian wrt v1
for j=length(rowJ)+1:total_state_size
    rowJ = [rowJ zeros(3,1)];
end
Jp = [Jp; rowJ];
% Jacobian of position error residual
rowJ = [];
rowJ = [rowJ zeros(3) zeros(3)]; % Jacobian wrt phi1 and v1
rowJ = [rowJ Ro(:,:,1)]; % Jacobian wrt p1
for j=length(rowJ)+1:total_state_size
    rowJ = [rowJ zeros(3,1)];
end
Jp = [Jp; rowJ];