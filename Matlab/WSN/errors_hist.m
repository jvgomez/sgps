real_pos = validdata(1,3:end);
n = length(real_pos)/2;

n_results = length(good_results_mid);
% Results errors
for i = 1: n_results
    errors(i,:) = abs(real_pos - results(i,6:15));
end

total_errors = [];
for i = 1:2:2*n
    total_errors = [total_errors; errors(:,i) errors(:,i+1) ];
end

n_data = length(validdata);
% Initial errors
for  i = 2: n_data
    init_errors(i,:) = abs(real_pos - validdata(i,3:12));
end

init_total_errors = [];
for i = 1:2:2*n
    init_total_errors = [init_total_errors; init_errors(:,i) init_errors(:,i+1) ];
end

perc_errors = [total_errors(:,1).*100./360 total_errors(:,2).*100./180];
perc_init_errors = [init_total_errors(:,1).*100./360 init_total_errors(:,2).*100./180];

n_results = n_results * n;
n_data = n_data * n;
[n_long ~] = hist(perc_errors(:,1),[0.25 0.5 0.75 1]);
[ni_long ~] = hist(perc_init_errors(:,1),[0.25 0.5 0.75 1]);
[n_lat ~] = hist(perc_errors(:,2),[1 2 3 4 5 6 7 8 9 10]);
[ni_lat ~] = hist(perc_init_errors(:,2),[1 2 3 4 5 6 7 8 9 10]);

disp('Longitude: Now Vs Initial');
n_long(1).*100./n_results
ni_long(1).*100./n_data

disp('Latitude: Now Vs Initial');
n_lat(1).*100./n_results
ni_lat(1).*100./n_data



