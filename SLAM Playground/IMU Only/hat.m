function y = hat(v)
if(size(v,1)*size(v,2)~=3)
    error('Hat function can only take a vector of 3 components');
end
    y = [0 -v(3) v(2);
        v(3) 0 -v(1);
        -v(2) v(1) 0];
end