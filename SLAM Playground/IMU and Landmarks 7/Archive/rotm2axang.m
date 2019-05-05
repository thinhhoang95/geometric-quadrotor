function y = rotm2axang(R)
phi=acos(0.5*(trace(R)-1));
if (phi<0.0005 && phi>-0.0005)
    y = [1 0 0 0];
else
    lgR=phi*(R-R')/(2*sin(phi));
    lgR=[lgR(3,2) lgR(1,3) lgR(2,1)];
    y = [lgR/norm(lgR) phi];
end
end