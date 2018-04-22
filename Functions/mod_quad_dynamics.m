
function [sys,x0,str,ts] = mod_quad_dynamics(t,x,u,flag, quad, x0, groundflag)

    % Completely rewritten for NLGC by Hoang Dinh Thinh
    % Email: thinh@neuralmetrics.net
    % Based on the S-Function template by Paul Ponds from Robotics Toolbox
    % by Peter Corke
    
    % Version 1.0 written 22/04/2018 - by Hoang Dinh Thinh
    % Revision is advised
    

    warning off MATLAB:divideByZero
    
    global groundFlag;
    
    % ARGUMENTS
    %   u       Reference inputs                1x4
    %   tele    Enable telemetry (1 or 0)       1x1
    %   crash   Enable crash detection (1 or 0) 1x1
    %   init    Initial conditions              1x12
    
    % INPUTS
    %   u = [N S E W]
    %   NSEW motor commands                     1x4
    
    % CONTINUOUS STATES
    %   z      Position                         1x3   (x,y,z)
    %   v      Velocity                         1x3   (xd,yd,zd)
    %   n      Attitude                         1x3   (Y,P,R)
    %   o      Angular velocity                 1x3   (wx,wy,wz)
    %   w      Rotor angular velocity           1x4
    %
    % Notes: z-axis downward so altitude is -z(3)
    
    % CONTINUOUS STATE MATRIX MAPPING
    %   x = [z1 z2 z3 n1 n2 n3 z1 z2 z3 o1 o2 o3 w1 w2 w3 w4]
    
    % INITIAL CONDITIONS
    n0 = [0 0 0];               %   n0      Ang. position initial conditions    1x3
    v0 = [0 0 0];               %   v0      Velocity Initial conditions         1x3
    o0 = [0 0 0];               %   o0      Ang. velocity initial conditions    1x3
    init = [x0 n0 v0 o0];       %   x0 is the passed initial position           1x3
    groundFlag = groundflag;

    % >>> CONTINUOUS STATE EQUATIONS <<<
    %   z` = v
    %   v` = g*e3 - (1/m)*T*R*e3
    %   I*o` = -o X I*o + G + torq
    %   R = f(n)
    %   n` = inv(W)*o
    
    % Dispatch the flag.
    %
    switch flag
        case 0
            [sys,x0,str,ts]=mdlInitializeSizes(init,quad); % Initialization
        case 1
            sys = mdlDerivatives(t,x,u,quad); % Calculate derivatives
        case 3
            sys = mdlOutputs(t,x,quad); % Calculate outputs
        case { 2, 4, 9 } % Unused flags
            sys = [];
        otherwise
            error(['Unhandled flag = ',num2str(flag)]); % Error handling
    end
end

%==============================================================
% mdlInitializeSizes
% Return the sizes, initial conditions, and sample times for the
% S-function.
% Parameters > init: intial translational position
% quad: quadrotor characteristic parameters
%==============================================================
%
function [sys,x0,str,ts] = mdlInitializeSizes(init,quad)
    %
    % Call simsizes for a sizes structure, fill it in and convert it
    % to a sizes array.
    %
    sizes = simsizes;
    sizes.NumContStates  = 12;
    sizes.NumDiscStates  = 0;
    sizes.NumOutputs     = 15;
    sizes.NumInputs      = 4;
    sizes.DirFeedthrough = 0;
    sizes.NumSampleTimes = 1;
    sys = simsizes(sizes);
    %
    % Initialize the initial conditions.
    x0 = init;
    %
    % str is an empty matrix.
    str = [];
    %
    % Generic timesample
    ts = [0 0];
    
    if quad.verbose
        disp(sprintf('t\t\tz1\t\tz2\t\tz3\t\tn1\t\tn2\t\tn3\t\tv1\t\tv2\t\tv3\t\to1\t\to2\t\to3\t\tw1\t\tw2\t\tw3\t\tw4\t\tu1\t\tu2\t\tu3\t\tu4'))
    end
end % End of mdlInitializeSizes.


%==============================================================
% mdlDerivatives
% Calculate the state derivatives for the next timestep
%==============================================================
%
function sys = mdlDerivatives(t,x,u,quad)
    global a1s b1s groundFlag
    
    %CONSTANTS
    %Cardinal Direction Indicies
    N = 1;                      %   N       'North'                             1x1
    E = 2;                      %   S       'South'                             1x1
    S = 3;                      %   E       'East'                              1x1
    W = 4;                      %   W       'West'                              1x1
    
    % Note that the notation D(:,i) simply implies that values are added
    % horizontally to the existing 1xn array.
    
    D(:,1) = [quad.d;0;quad.h];          %   Di      Rotor position in body fr  1x3
    D(:,2) = [0;quad.d;quad.h];
    D(:,3) = [-quad.d;0;quad.h];
    D(:,4) = [0;-quad.d;quad.h];
    
    %Body-fixed frame references
    e1 = [1;0;0];               %   ei      Body fixed frame references         3x1
    e2 = [0;1;0];
    e3 = [0;0;1];
    
    %EXTRACT ROTOR SPEEDS FROM U
    w = u(1:4);
    
    %EXTRACT STATES FROM X
    z = x(1:3);   % position in inertial frame
    n = x(4:6);   % YPR angles inertial frame
    v = x(7:9);   % velocity in inertial frame
    o = x(10:12); % angular rates in body frame
    
    %PREPROCESS ROTATION AND WRONSKIAN MATRICIES
    phi = n(1);    % yaw
    the = n(2);    % pitch
    psi = n(3);    % roll
    
    R = [cos(the)*cos(phi) sin(psi)*sin(the)*cos(phi)-cos(psi)*sin(phi) cos(psi)*sin(the)*cos(phi)+sin(psi)*sin(phi);   %BBF > Inertial rotation matrix
         cos(the)*sin(phi) sin(psi)*sin(the)*sin(phi)+cos(psi)*cos(phi) cos(psi)*sin(the)*sin(phi)-sin(psi)*cos(phi);
         -sin(the)         sin(psi)*cos(the)                            cos(psi)*cos(the)];
    
    % The above R is constructed via the following process (Tait-Bryat
    % angles) in Z-Y-X order: rotz(phi)*roty(the)*rotx(psi).
    % Note that phi is the yaw angle (RZ), the is the pitch angle (RY) and
    % psi is the roll angle (RX).
    %     Q3 = [cos(phi) -sin(phi) 0;sin(phi) cos(phi) 0;0 0 1];   % RZ
    %     Q2 = [cos(the) 0 sin(the);0 1 0;-sin(the) 0 cos(the)];   % RY
    %     Q1 = [1 0 0;0 cos(psi) -sin(psi);0 sin(psi) cos(psi)];   % RX
    %     R = Q3*Q2*Q1    %Rotation matrix
    %     or R = RZ * RY * RX
    
    % The following matrix transforms an angular rates written in body
    % frame to angular velocity in inertial frame.
    
    iW = [0        sin(psi)          cos(psi);             
          0        cos(psi)*cos(the) -sin(psi)*cos(the);
          cos(the) sin(psi)*sin(the) cos(psi)*sin(the)] / cos(the);
      
    if any(w == 0)
        % might need to fix this, preculudes aerobatics :(
        % mu becomes NaN due to 0/0
        error('mod_quad_dynamics: not defined for zero rotor speed');
    end
    
    %ROTOR MODEL
    for i=[N E S W] %for each rotor
        %Relative motion
        
        Vr = cross(o,D(:,i)) + v;
        mu = sqrt(sum(Vr(1:2).^2)) / (abs(w(i))*quad.r);  %Magnitude of mu, planar components
        lc = Vr(3) / (abs(w(i))*quad.r);   %Non-dimensionalised normal inflow
        li = mu; %Non-dimensionalised induced velocity approximation
        alphas = atan2(lc,mu);
        j = atan2(Vr(2),Vr(1));  %Sideslip azimuth relative to e1 (zero over nose)
        J = [cos(j) -sin(j);
            sin(j) cos(j)];  %BBF > mu sideslip rotation matrix
        
        %Flapping
        beta = [((8/3*quad.theta0 + 2*quad.theta1)*mu - 2*(lc)*mu)/(1-mu^2/2); %Longitudinal flapping
            0;];%sign(w) * (4/3)*((Ct/sigma)*(2*mu*gamma/3/a)/(1+3*e/2/r) + li)/(1+mu^2/2)]; %Lattitudinal flapping (note sign)
        beta = J'*beta;  %Rotate the beta flapping angles to longitudinal and lateral coordinates.
        a1s(i) = beta(1) - 16/quad.gamma/abs(w(i)) * o(2);
        b1s(i) = beta(2) - 16/quad.gamma/abs(w(i)) * o(1);
        
        %Forces and torques
        % T(:,i) = quad.Ct*quad.rho*quad.A*quad.r^2*w(i)^2 * [-cos(b1s(i))*sin(a1s(i)); sin(b1s(i));-cos(a1s(i))*cos(b1s(i))];   % Rotor thrust, linearised angle approximations
        T(:,i) = quad.Ct*quad.rho*quad.A*quad.r^2*w(i)^2;   % Rotor thrust, no flapping approximations
        Q(:,i) = -quad.Cq*quad.rho*quad.A*quad.r^3*w(i)*abs(w(i)) * e3;     % Rotor drag torque - note that this preserves w(i) direction sign
        tau(:,i) = cross(T(:,i),D(:,i));    % Torque due to rotor thrust
    end
    
    %RIGID BODY DYNAMIC MODEL
    dz = v; % x` = v
    dn = iW*o; % since o is angular rates in BF, iW*o gives angular velocity in inertial frame
    
    dv = quad.g*e3 + R*(1/quad.M)*sum(T,2); % sum(T,2) sums thrusts on all rotors. v` = ge3 - fRe3.
    
    % vehicle can't fall below ground
    if groundFlag && (z(3) > 0)
        z(3) = 0;
        dz(3) = 0;
    end
    do = inv(quad.J)*(cross(-o,quad.J*o) + sum(tau,2) + sum(Q,2)); %row sum of torques, derivation of angular rates relates to the moment equation
    sys = [dz;dn;dv;do];   %This is the state derivative vector
end % End of mdlDerivatives.


%==============================================================
% mdlOutputs
% Calculate the output vector for this timestep
%==============================================================
%
function sys = mdlOutputs(t,x,quad)
    
    %TELEMETRY
    if quad.verbose
        disp(sprintf('%0.3f\t',t,x))
    end
    
    % compute output vector as a function of state vector
    %   z      Position                         3x1   (x,y,z)
    %   v      Velocity                         3x1   (xd,yd,zd)
    %   n      Attitude                         3x1   (Y,P,R)
    %   o      Angular velocity                 3x1   (Yd,Pd,Rd)
    
    n = x(4:6);    % YPR angles
    phi = n(1);    % yaw
    the = n(2);    % pitch
    psi = n(3);    % roll
    
    
    % This is the same rotation matrix as above
    R = [cos(the)*cos(phi) sin(psi)*sin(the)*cos(phi)-cos(psi)*sin(phi) cos(psi)*sin(the)*cos(phi)+sin(psi)*sin(phi);   %BBF > Inertial rotation matrix
         cos(the)*sin(phi) sin(psi)*sin(the)*sin(phi)+cos(psi)*cos(phi) cos(psi)*sin(the)*sin(phi)-sin(psi)*cos(phi);
         -sin(the)         sin(psi)*cos(the)                            cos(psi)*cos(the)];
    
    iW = [0        sin(psi)          cos(psi);             % from body rates to inertial angular velocity
          0        cos(psi)*cos(the) -sin(psi)*cos(the);
          cos(the) sin(psi)*sin(the) cos(psi)*sin(the)] / cos(the);
    
    % return velocity in the body frame
    sys = [ x(1:6);
            inv(R)*x(7:9);   % Translational velocity in body frame
            % iW*x(10:12); % Angular velocity in inertial frame
            x(10:12); % Angular rates in body frame
            x(7:9)];    % Velocity in inertial frame
    % sys = x;
end
% End of mdlOutputs.
