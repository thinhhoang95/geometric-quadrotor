## Geometric Nonlinear Control MATLAB/Simulink Implementation

### Introduction

Author: Hoang Dinh Thinh (thinh@neuralmetrics.net), Department of Aeronautical Engineering, Ho Chi Minh City University of Technology, Vietnam.

This is a discrete implementation of a nonlinear tracking control algorithm for a quadrotor with a slight modification specifically on the attitude moment. You are highly encouraged to read the original paper: "Geometric Tracking Control of a Quadrotor UAV on SE(3)" by Taeyoung Lee, Melvin Leok, N. Harris McClamroch (https://arxiv.org/abs/1003.2005v1).

You are free to modify this software to suit your needs. This software is not perfect, and your feedback is greatly appreciated. I will try to fix bugs if I find more, and in the future, I will continue uploading C/C++ code for Arduino if you are a hobbyist.

This software also comes with a simplified Quadrotor model that relaxed all the hassles when it comes to rotation order, inertial frame or body frame. However, this model still uses Euler Angle representation, which is inarguably not a good way to represent an airplane's attitude, but this is a good way to grasp the intuition of how the airplane is moving in 3D space just by looking at the roll, pitch and yaw angles. Perhaps you could help me the quarternion?

Finally, hope you will have a lot of fun whether you are conducting research or just trying something new. If you have any question, please do not hesitate to contact me via my email listed above.

### Getting started
Open the Simulink project, then navigate to SML Quadrotor Simulations, Synthesis and pick one of the two examples: attitude tracking or position tracking.

Detailed documentation of the software can be found in my thesis at https://www.researchgate.net/publication/325655279_Application_and_simulation_of_nonlinear_geometric_control_for_Quadrotor_UAVs. Chapter 4 describes the inputs ant outputs of the blocks. Users interested in theoretical foundation might find chapter 3 helpful. 

### License
Copyright 2018 (c) NeuralMetrics SA

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
