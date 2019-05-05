function R = axang2rotm(phix)
if (phix(4)<0.0005 && phix(4)>-0.0005)
    R = eye(3);
else
    phi = phix(4) * phix(1:3);
    R = eye(3) + sin(norm(phi))/norm(phi) * hat(phi) + (1-cos(norm(phi)))/(norm(phi)^2) * hat(phi) * hat(phi);
end
end