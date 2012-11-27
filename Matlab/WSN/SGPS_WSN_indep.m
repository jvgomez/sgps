%% NOTA MENTAL: olvidarnos de los pol�gonos y tratar de optimizar la posici�n de cada uno 
%%de los sensores minimizando la distancia de mahalanobis (o euclidea o  haversiana) al punto original
%%dado por sgps y minimizando la diferencia de distancias con respecto a las
%%medidas entre sensores. Differential evolution 2 par�metros por sensor.

% clear all;
% close all;

%% Trotar y transladar hasta conseguir el mejor fitness. Haria falta
%%meter escalas horitonzales y verticales? Yo creo que si, aunque se puede
%%evitar confiando en las posiciones iniciales dadas por SGPS.

%% Modeling error in Mu (means) and Sigma (covariances)
load('data/errors');
mu = [ mean(error_longitudes) mean(error_latitudes)];
vvar = [var(error_longitudes) var(error_latitudes)]; 
sigma = cov([ error_longitudes error_latitudes ]);
clear error_latitudes error_longitudes;

%% Reading data
%load('data/validdata5');
load('data/testdata5');

aux = size(validdata(1,:));

n = (aux(2)-2)/2; % Number of nodes.

for i = 1:n
    real_pos(i,:) = validdata(1,2*i+1:2*i+2); % Lat - Long
end

%% Computing distances between real stations.
% Using the real distances in km.
for i = 1:n
    for j = i:n
        % We need to add noise here.
        D(i,j) = haversine(real_pos(i,1), real_pos(i,2), real_pos(j,1), real_pos(j,2));
    end
end

%% Plotting real stations.
%  geoshow('landareas.shp', 'FaceColor', [0.5 1.0 0.5]);
%  hold on;
%  scatter(real_pos(:,1), real_pos(:,2),'rx');
%  title('Real locations');

%% Differential evolution parameters.
VTR = 1.e-6;                    % Value to reach in the optimization.
%VTR = -Inf;
n_param = 2*n;                  % Number of parameters.
NP = 10*n;                       % Population.
itermax = 1000;                   % Maximum iterations.
F = 0.7;                        % DE-stepsize.
CR = 1;                       % Crossover probability
strategy = 9;                   % Strategy: DE/rand/1/bin
refresh = 0;                    % Output refresh (iterations)

aux_1 = [-180 -90];
aux_2 = [180 90];
XVmin = [];
XVmax = [];

for i = 1:n
    XVmin = [XVmin aux_1];      % Lower bounds for the initial population.
    XVmax = [XVmax aux_2];      % Upper bounds for the initial population.
end

eval.mu = mu;
eval.vvar = vvar;
eval.SIGMA = sigma;
eval.D = D;
%eval.alpha = 0.0005; %Relative weight of the distance among nodes against mahalanobis
                % distance to the sgps original position.

eval.alpha = 0.5;

results = [];
%% Differential evolution for every day and symmetry of the polygon.
% Reading initial SGPS results.
for j = 2:length(validdata) % For every day, first row are real
%coordinates.
%aux_test = 1+ 1;
%for j = aux_test:aux_test
tic;
    disp(sprintf('Iteration %d of %d.', j, length(validdata)))
    for i = 1:n
        sgps_pos(i,:) = validdata(j, 2*i+1 : 2*i+2); % Read that day, 
    end

    day = validdata(j, 1);
    year = validdata(j, 2);
    
    eval.sgps_pos = sgps_pos;
    % x: best member of population.
    % f: best fitness.
    % nf: number of function evaluations.
    [x,f,nf] = gavec3('sgps_fitness_indep', VTR, n_param, XVmin, XVmax, eval, NP, itermax, F, CR, strategy, refresh);
    %[x,f,nf] = gavec3('sgps_fitness_prob', VTR, n_param, XVmin, XVmax, eval, NP, itermax, F, CR, strategy, refresh);
    
    final_pos = reshape(x,2,n)';
    
    for z = 1:n % Converting longitude into [-180,180]
        aux_l = final_pos(z,1);
        aux_l = mod(aux_l,360);
        
        if 180 < aux_l && aux_l < 360
            aux_l = aux_l - 360;
        end
        final_pos(z,1) = aux_l;
    end
    
    for z = 1:n % Converting latitude into [-90,90]
        aux_l = final_pos(z,2);
        aux_l = mod(aux_l,360);
        
        
        
        if 90 < aux_l && aux_l <= 270
            aux_l = -aux_l + 180;
        elseif 270 < aux_l && aux_l < 360
            aux_l = aux_l - 360;
        end
        final_pos(z,2) = aux_l;
    end
    
    init_error = 0;
    final_error = 0;
    for k = 0:n-1
    	init_error = init_error + haversine(sgps_pos(k+1, 1),  sgps_pos(k+1, 2), real_pos(k+1, 1),  real_pos(k+1, 2));
        final_error = final_error + haversine( final_pos(k+1, 1),   final_pos(k+1, 2), real_pos(k+1, 1),  real_pos(k+1, 2));
    end
    
    results = [results; day year init_error final_error f x];
    
    disp(sprintf('Initial error: %f', init_error));
    disp(sprintf('Final error:   %f', final_error));
toc;
end

% Create figure and axes.
figure1 = figure;
axes1 = axes('Parent',figure1);
hold(axes1,'all');
% World plot.
%geoshow('landareas.shp', 'FaceColor', [0.5 1.0 0.5]);
%hold on;
title('Results');
scatter(real_pos(:,1), real_pos(:,2), 'rx', 'Parent', axes1, 'DisplayName','Real location');
hold on;
scatter(sgps_pos(:,1), sgps_pos(:,2), 'bo', 'Parent', axes1,'DisplayName','SGPS location');
scatter(final_pos(:,1), final_pos(:,2), 'g.', 'Parent', axes1, 'DisplayName', 'SGPS-WSN location');

% Create legend
legend1 = legend(axes1,'show');
set(legend1,'Orientation','horizontal','Location','NorthOutside');

for i = 1 : n
    line([real_pos(i,1) final_pos(i,1)],[real_pos(i,2) final_pos(i,2)], 'Color','g');
    line([real_pos(i,1) sgps_pos(i,1)],[real_pos(i,2) sgps_pos(i,2)], 'Color','b');
end