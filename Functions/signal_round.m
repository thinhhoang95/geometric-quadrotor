function y = signal_round(x)
% This function should be called whenever a chain of calculations may result
% in very small signal amplitude. 
% A rule of thumb is if the signal may go to zero, it's necessary to impose
% rounding upon it.
y = round(x*10e6)/10e6;
end