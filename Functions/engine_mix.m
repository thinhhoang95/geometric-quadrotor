function [o1,o2,o3,o4] = engine_mix(f,M,Ct,dctcq)
force = [f; M];
gamma = [Ct Ct Ct Ct;
    dctcq];
omega_sq = gamma\force;
omega=zeros(4,1);
for i=1:4
    if omega_sq(i)>0
        omega(i)=sqrt(omega_sq(i));
    else
        omega(i)=0;
    end
end
o1=omega(1);
o2=omega(2);
o3=omega(3);
o4=omega(4);