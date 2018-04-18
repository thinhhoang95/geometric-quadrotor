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
% if (isalmost(theta,0,10e-6))
%     Omega=[0;0;0];
% else
%     OmegaS = 1/(2*Ts) * theta/sin(theta) * (A-A');
%     Omega = vee(OmegaS);
% end
Omega = inv(rpy2jac(tr2rpy(Rf)))*(tr2rpy(Rf)-tr2rpy(Ri))'/Ts;
