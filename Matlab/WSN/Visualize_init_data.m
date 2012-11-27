load('data/testdata5');

aux = size(validdata(1,:));

n = (aux(2)-2)/2; % Number of nodes.

cc = hsv(n);

for i = 1:n
    real_pos(i,:) = validdata(1,2*i+1:2*i+2); % Lat - Long
end

figure(1)
hold on;
for j = 2:length(validdata)
    validdata(j,1)
    for i = 1:n
        sgps_pos(i,:) = validdata(j, 2*i+1 : 2*i+2); % Read that day, 
    end

    scatter(real_pos(:,1), real_pos(:,2), 'rx');
    
    for k = 1:n
        scatter(sgps_pos(k,1), sgps_pos(k,2), 'o', 'MarkerEdgeColor',cc(k,:));
    end
    pause;
 end