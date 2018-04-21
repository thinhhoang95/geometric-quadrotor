function Omega = rr2ar(Ri,Rf,Ts)
% A DISCRETE IMPLEMENTATION OF ANGULAR RATES ESTIMATION (IN BODY FIXED
% FRAME). Input will be 2 rotation matrices B>I, described in ZYX rotation.
% A = Rf*Ri';
% term = (trace(A)-1)/2;
% if isalmost(term,1,10e-6)
%     term = 1;
% elseif isalmost(term,-1,10e-6)
%     term = -1;
% end
% theta = acos(term);
% if (isalmost(theta,0,10e-12))
%     Omega=[0;0;0];
% else
%     OmegaS = 1/(2*Ts) * theta/sin(theta) * (A-A');
%     Omega = vee(OmegaS);
% end
% Omega=vee(A)/Ts;
% 
% Another implementation based on Wronskian of Euler Angles
eul_angles = mod_tr2rpy(Rf)';
phi = eul_angles(3); % yaw
the = eul_angles(2); % pitch
psi = eul_angles(1); % roll

eul_angles_i = mod_tr2rpy(Ri)';
phi_i = eul_angles_i(3); % yaw
the_i = eul_angles_i(2); % pitch
psi_i = eul_angles_i(1); % roll

iW = [0        sin(psi)          cos(psi);             %inverted Wronskian
      0        cos(psi)*cos(the) -sin(psi)*cos(the);
      cos(the) sin(psi)*sin(the) cos(psi)*sin(the)] / cos(the);

Omega = iW*([phi-phi_i the-the_i psi-psi_i])'/Ts; % yaw-pitch-roll rate

% Another implementation
% rpy2 = mod_tr2rpy(Rf);
% rpy1 = mod_tr2rpy(Ri);
% 
% phi = rpy2(3);
% the = rpy2(2);
% psi = rpy2(1);
% 
% B = [1, sin(phi)*tan(the), cos(phi)*tan(the)
%     0, cos(phi), -sin(phi)
%     0, sin(phi)*sec(the), cos(phi)*sec(the)];
% 
% drpy = (rpy2-rpy1)/Ts;
% Omega = inv(B)*drpy;