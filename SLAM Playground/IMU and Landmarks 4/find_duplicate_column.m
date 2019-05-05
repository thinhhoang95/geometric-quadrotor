Jt = J';
for q=1:size(J',1)
    for r=q+1:size(J',1)
        compar = Jt(q,:)==Jt(r,:);
        if(sum(compar)==81)
            fprintf('Found matching columns %d and %d', [q, r]);
        end
    end
end