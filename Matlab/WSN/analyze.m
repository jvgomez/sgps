load('Results.mat');
ind = find(results(:,3)<results(:,4));
indd = find(results(:,3)>results(:,4));
ind2 = [];
ind22 = [];
indd2 = [];
indd22 = [];

for i = 1:length(ind)
    j = ind(i);
    
    if results(j,1) > 81 && results(j,1)<266
        ind2 = [ind2; j]; % Days between 81 and 266 which has worse results than initial ones.
    else
        ind22 = [ind22; j]; % Days between 266 and 81 which has worse results than initial ones.
    end
end

for i = 1:length(indd)
    j = indd(i);
     if results(j,1) > 81 && results(j,1) < 266
         indd2 = [indd2; j];
     else 
         indd22 = [indd22; j];
     end
    
end

ind3 = [];
for i = 1:length(results)
    if results(i,1) > 81 && results(i,1) < 266
        ind3 = [ind3; i]; % Days in general between 81 and 266.
    end
end

% Splitting days but adding the indices from validdata files to track them.
bad_results_sides = [ind22 results(ind22,:)];
bad_results_mid = [ind2 results(ind2,:)];
good_results_sides =  [indd22 results(indd22,:)];
good_results_mid =  [indd2 results(indd2,:)];