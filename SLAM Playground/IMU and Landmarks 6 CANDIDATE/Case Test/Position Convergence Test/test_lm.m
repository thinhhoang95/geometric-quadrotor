%% TEST LANDMARK OPTIMIZATION
% The purpose of this file is to test the validity of Jacobian when optimizing on 2D photometric error 

clear all;
clc;

focal_length = 0.024;

% True entities
Lt = [0 0 0; 1 0 0; 0 1 0; -1 1 0; -2 -1.5 0; 2 0.5 0];
Pt = [0 0 -4];
Rt = eul2rotm([6 15 21] * pi / 180);

num_of_landmarks = size(Lt,1);
total_state_size = 6 + num_of_landmarks * 3;

% Estimated entities
Lo = [0 0 0; 0 0 0; 0 0 0; 0 0 0; 0 0 0; 0 0 0];
Po = [1 1 -4];
Ro = eye(3);

% Gauss Newton solve
cost_fn = [];
for iter=1:500
    run('calculate_rj');
    H = J'*J;
    b = -J'*residual';
    delta = pinv(H)*b;
    if (iter==25)
        fprintf('Debug \n');
    end
    fprintf('Iteration %d: Current cost function %f \n', [iter, residual*residual']);
    cost_fn = [cost_fn residual*residual'];
    % Update attitude
    Ro = Ro*axang2rotm([delta(1:3)'/norm(delta(1:3)) norm(delta(1:3))]);
    Po = Po+(Ro*delta(4:6))';
    for lm=1:num_of_landmarks
        lmof = 6+(lm-1)*3+1;
        lmot = lmof+2;
        Lo(lm,:) = Lo(lm,:) + delta(lmof:lmot)';
    end
end
plot(cost_fn);