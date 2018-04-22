function [f,M] = omega2force(o1,o2,o3,o4,ct,dctcq)
gamma = [ct ct ct ct;
    dctcq];
rotor_speed = [o1;o2;o3;o4];
thrust = signal_round(gamma * rotor_speed.^2); % get rid of annoying numerical error due to sqrt
f = thrust(1) * [0 0 -1]';
M = [thrust(2); thrust(3); thrust(4)];
end