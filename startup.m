clear all;
clc;

fprintf('NLGC Quadrotor 1.0 - Geometric Tracking Control Simulation\n');
fprintf('By Hoang Dinh Thinh (thinh@neuralmetrics.net)\n');
fprintf('Built upon QuadSim - Copyright GPL LESSER. All rights reserved.\n');

addpath('Graphical User Interfaces');
addpath('Functions');
quadModel = importdata('Quadcopter Structure Files/quadModel_X.mat');
IC = importdata('Initial Conditions/IC_HoverAt10ft.mat');
Path = importdata('Path Command Files/Path_Diamond.mat');