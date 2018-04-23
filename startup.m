clear all;
clc;

fprintf('NLGC Quadrotor 2.0 - Geometric Tracking Control Simulation\n');
fprintf('By Hoang Dinh Thinh (thinh@neuralmetrics.net)\n');
fprintf('Now starting Robotics Toolbox... Visit http://petercorke.com/wordpress/toolboxes/robotics-toolbox\n');

run('rvctools/startup_rvc.m');

fprintf('Resolving directories...\n');
% Search directories
addpath('Graphical User Interfaces');
addpath('Functions');
addpath('SML Addon Models');

fprintf('Loading sample paths...\n');
% Quadrotor dynamics, initial condition and position tracking path data
% quadModel = importdata('Quadcopter Structure Files/quadModel_X.mat');
% IC = importdata('Initial Conditions/IC_HoverAt10ft.mat');
Path = importdata('Path Command Files/Path_Diamond.mat');

% Some variable initialisations
t=Path.x.Time;
x=reshape(Path.x.data(1,1,:),[7,1]);
y=reshape(Path.y.data(1,1,:),[7,1]);
z=reshape(Path.z.data(1,1,:),[7,1]);
psi=reshape(Path.psi.data(1,1,:),[7,1]);

% quadModel.J = diag([quadModel.Jx; quadModel.Jy; quadModel.Jz]);

% Reupdate some path - for debugging purpose
x=[0;0;0;0;0;0;0];
y=[0;0;0;0;0;0;0];
z=[-4;-4;-4;-4;-4;-4;-4];

fprintf('Initialising quadrotor struct...\n');
% Initialise quadrotor struct
run('quad_struct_init');

fprintf('Startup complete!\n');

% Bus types declarations

% % For Flight Director Block
% 
% % CyanBus: contains calculated desired thrust direction (b3c) and thrust
% % magnitude to apply (f)
% clear CyanBus;
% 
% CyanBus(1) = Simulink.BusElement;
% CyanBus(1).Name = 'ThrustDirection';
% CyanBus(1).Dimensions = [3 1];
% CyanBus(1).DimensionsMode = 'Fixed';
% CyanBus(1).DataType = 'double';
% CyanBus(1).SampleTime = -1;
% CyanBus(1).Complexity = 'real';
% 
% CyanBus(2) = Simulink.BusElement;
% CyanBus(2).Name = 'ThrustMagnitude';
% CyanBus(2).Dimensions = 1;
% CyanBus(2).DimensionsMode = 'Fixed';
% CyanBus(2).DataType = 'double';
% CyanBus(2).SampleTime = -1;
% CyanBus(2).Complexity = 'real';