function moment = nlgc_moment(J,O,R,Od,Odd,Rd,er,eo,kr,ko)
moment = hat(O)*(J*O) - J*(hat(O)*R'*Rd*Od - R'*Rd*Odd + kr * er + ko * eo); % Original NLGC
%moment = -J*(kr*er + ko*eo); % PD controller - simplified