%% TEST LANDMARK OPTIMIZATION
% The purpose of this file is to test the validity of Jacobian when optimizing on 2D photometric error 

clear all;
clc;

focal_length = 0.024;
num_of_kf = 2;

% True entities
Lt = [0 0 0];
Pt = [0 0 -4; 
    1 1 -4];
Rt = [];
Rt(:,:,1) = eul2rotm([6 15 21] * pi / 180);
Rt(:,:,2) = eul2rotm([3 12 21] * pi /180);

num_of_landmarks = size(Lt,1);
total_state_size = 0 + num_of_landmarks * 3;

% Estimated entities
Lo = [-1 -2 -4];
Po = Pt;
Ro = Rt;

% Gauss Newton solve
cost_fn = [];

    for iter=1:20
        run('calculate_rj_3pos');
        H = J'*J;
        b = -J'*residual';
        delta = inv(H)*b;
        if (iter==25)
            fprintf('Debug \n');
        end
        fprintf('Iteration %d: Current cost function %f \n', [iter, residual*residual']);
        cost_fn = [cost_fn residual*residual'];
        % Update attitude
        % Ro = Ro*axang2rotm([delta(1:3)'/norm(delta(1:3)) norm(delta(1:3))]);
        % Po = Po+(Ro*delta(4:6))';
        for lm=1:num_of_landmarks
            lmof = (lm-1)*3+1;
            lmot = lmof+2;
            Lo(lm,:) = Lo(lm,:) + delta(lmof:lmot)';
        end
    end

plot(cost_fn);