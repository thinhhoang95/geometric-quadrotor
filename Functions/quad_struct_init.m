quad.J = diag([0.082 0.082 0.149]); % kg.m^2
quad.m = 4; % kg
quad.g = 9.81; % m/s^2
quad.ct = 0.0048;
quad.cq = 2.3515e-04;
quad.d = 0.315;
dct = quad.d*quad.ct;
cq = quad.cq;
quad.dctcq = [0 dct 0 -dct;
    -dct 0 dct 0;
    -cq cq -cq cq];
clear dct cq;