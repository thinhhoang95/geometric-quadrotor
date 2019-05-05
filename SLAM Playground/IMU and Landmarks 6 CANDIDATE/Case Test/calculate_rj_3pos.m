residual = [];
for kf=1:num_of_kf
    for lmi=1:num_of_landmarks
        % Residual calculation
        % True landmark location
        true_pl = Rt(:,:,kf)' * (Lt(lmi,:)-Pt(kf,:))';
        true_pli = focal_length * [true_pl(1)/true_pl(3) true_pl(2)/true_pl(3)];
        % Predicted landmark location
        pr_pl = Ro(:,:,kf)' * (Lo(lmi,:)-Po(kf,:))';
        pr_pli = focal_length * [pr_pl(1)/pr_pl(3) pr_pl(2)/pr_pl(3)];
        % Photometric error residual
        r = pr_pli - true_pli;
        residual = [residual r];
    end
end

J = [];
% Jacobian calculation
for kf=1:num_of_kf
    rowJ = [];
    % Jacobian of photometric error wrt phi1
    Gamma = Ro(:,:,kf)' * (Lo - Po(kf,:))';
    xp = Gamma(1); yp = Gamma(2); zp = Gamma(3);
    % dGdP = hat(Ro' * (Lo(lmi,:) - Po)');
    % addToRowJ = focal_length * [(dGdP(1,1)*zp - dGdP(3,1)*xp)/zp^2 (dGdP(1,2)*zp - dGdP(3,2)*xp)/zp^2 (dGdP(1,3)*zp - dGdP(3,3)*xp)/zp^2;
    %     (dGdP(2,1)*zp - dGdP(3,1)*yp)/zp^2 (dGdP(2,2)*zp - dGdP(3,2)*yp)/zp^2 (dGdP(2,3)*zp - dGdP(3,3)*yp)/zp^2];
    % rowJ = [rowJ dGdP]; % Allow update attitude
    % rowJ = [rowJ zeros(2,3)]; % Do not update attitude
    % Jacobian of photometric error wrt p1
    dGdPos = -eye(3);
    addToRowJ = focal_length * [(dGdPos(1,1)*zp - dGdPos(3,1)*xp)/zp^2 (dGdPos(1,2)*zp - dGdPos(3,2)*xp)/zp^2 (dGdPos(1,3)*zp - dGdPos(3,3)*xp)/zp^2;
        (dGdPos(2,1)*zp - dGdPos(3,1)*yp)/zp^2 (dGdPos(2,2)*zp - dGdPos(3,2)*yp)/zp^2 (dGdPos(2,3)*zp - dGdPos(3,3)*yp)/zp^2];
    % rowJ = [rowJ zeros(2,3)]; % Do not update position
    % rowJ = [rowJ dGdPos]; % Allow update position
    % Jacobian of photometric error wrt Lo (landmark position)
    % First, fill in all intermediate columns with zero
    for j=(length(rowJ)+1):(total_state_size-(num_of_landmarks-1+1)*3)
        rowJ = [rowJ zeros(3,1)];
    end
    % Jacobian wrt landmark position
    dGdPos = Ro(:,:,kf)';
    addToRowJ = focal_length * [(dGdPos(1,1)*zp - dGdPos(3,1)*xp)/zp^2 (dGdPos(1,2)*zp - dGdPos(3,2)*xp)/zp^2 (dGdPos(1,3)*zp - dGdPos(3,3)*xp)/zp^2;
        (dGdPos(2,1)*zp - dGdPos(3,1)*yp)/zp^2 (dGdPos(2,2)*zp - dGdPos(3,2)*yp)/zp^2 (dGdPos(2,3)*zp - dGdPos(3,3)*yp)/zp^2];
    rowJ = [rowJ addToRowJ];
    for j=(length(rowJ)+1):(total_state_size)
        rowJ = [rowJ zeros(3,1)];
    end
    J = [J; rowJ];
end