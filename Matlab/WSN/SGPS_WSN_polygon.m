%% NOTA MENTAL: olvidarnos de los polígonos y tratar de optimizar la posición de cada uno 
%%de los sensores minimizando la distancia de mahalanobis (o euclidea o  haversiana) al punto original
%%dado por sgps y minimizando la diferencia de distancias con respecto a las
%%medidas entre sensores. Differential evolution 2 parámetros por sensor.

clear all;
close all;

%% Trotar y transladar hasta conseguir el mejor fitness. Haria falta
%%meter escalas horitonzales y verticales? Yo creo que si, aunque se puede
%%evitar confiando en las posiciones iniciales dadas por SGPS.

%% Modeling error in Mu (means) and Sigma (covariances)
load('data/errors');
mu = [mean(error_longitudes) mean(error_latitudes)];
sigma = cov([error_longitudes error_latitudes]);
clear error_latitudes error_longitudes;

%% Reading data
load('data/validdata5');

aux = size(validdata(1,:));

n = (aux(2)-2)/2; % Number of nodes.

for i = 1:n
    realpos(i,:) = validdata(1,2*i+1:2*i+2); % Lat - Long
end

%% Computing distances between real stations.
% Using coordinates-based distances.
for i = 2:n
    D(1,i) = euc_dist([realpos(1,1), realpos(1,2)]', [realpos(i,1), realpos(i,2)]');
    D(2,i) = euc_dist([realpos(2,1), realpos(2,2)]', [realpos(i,1), realpos(i,2)]');
    D(i-1,i) = euc_dist([realpos(i-1,1), realpos(i-1,2)]', [realpos(i,1), realpos(i,2)]');
end

% Using the real distances in km.
% for i = 2:n
%     %for j = [1, 2, i];
%     D(1,i) = haversine(realpos(1,1), realpos(1,2), realpos(i,1), realpos(i,2));
%     D(2,i) = haversine(realpos(2,1), realpos(2,2), realpos(i,1), realpos(i,2));
%     D(i-1,i) = haversine(realpos(i-1,1), realpos(i-1,2), realpos(i,1), realpos(i,2));
% end

%% Plotting real stations.
%  geoshow('landareas.shp', 'FaceColor', [0.5 1.0 0.5]);
%  hold on;
%  scatter(realpos(:,2), realpos(:,1),'rx');
%  title('Real locations');

%% Creating the base shape based on distances.
nodes = create_polygon(D);

%% Plotting the polygon.
%  figure; hold on;
%  plot_nodes(nodes);

%% Differential evolution parameters.
VTR = 1.e-6;                    % Value to reach in the optimization.
n_param = 3;                    % Number of parameters.
XVmin = [-180, -90, 0.0];       % Lower bounds.
XVmax = [ 180,  90, 2*pi];      % Upper bounds.
NP = 100;                       % Population.
itermax = 50;                   % Maximum iterations.
F = 0.6;                        % DE-stepsize.
CR = 0.8;                       % Crossover probability
strategy = 7;                   % Strategy: DE/rand/1/bin
refresh = 0;                    % Output refresh (iterations)

eval.mu = mu;
eval.SIGMA = sigma;
%% Differential evolution for every day and symmetry of the polygon.

% Reading initial SGPS results.
%for j = 2:length(validdata) % For every day, first row are real
%coordinates.
for j = 2:2
    for i = 1:n
        sgps_pos(i,:) = validdata(j, 2*i+1:2*i+2); % Read that day, 
    end

    eval.sgps_pos = sgps_pos;
    eval.nodes = nodes;

    tic();
    
    % best member of population.
    % best fitness.
    % number of function evaluations.
    % 4 times so the 4 possible symmetries are tested.
    [x1,f1,nf1] = gavec3('sgps_fitness', VTR, n_param, XVmin, XVmax, eval, NP, itermax, F, CR, strategy, refresh);
    eval.nodes = symmetry(nodes, 0);
    [x2,f2,nf2] = gavec3('sgps_fitness', VTR, n_param, XVmin, XVmax, eval, NP, itermax, F, CR, strategy, refresh);
    eval.nodes = symmetry(nodes, 1);
    [x3,f3,nf3] = gavec3('sgps_fitness', VTR, n_param, XVmin, XVmax, eval, NP, itermax, F, CR, strategy, refresh);
    eval.nodes = symmetry(nodes, 0);
    eval.nodes = symmetry(eval.nodes, 1);
    [x4,f4,nf4] = gavec3('sgps_fitness', VTR, n_param, XVmin, XVmax, eval, NP, itermax, F, CR, strategy, refresh);

    xx = [x1; x2; x3; x4];
    ff = [f1; f2; f3; f4];
    f = Inf;
    symm = 0;
    for i = 1:4 %Looking for the best transformation among the 4 tested.
        if ff(i) < f
            f = ff(i);
            x = xx(i,:);
            if i > 1 % To memorize the symmetry applied.
                symm = i;
            end
        end
    end
    
	toc();
    
    transf_nodes = nodes;
    switch symm
        case 2
            transf_nodes = symmetry(transf_nodes, 0);  
        case 3
            transf_nodes = symmetry(transf_nodes, 1);  
        case 4
            transf_nodes = symmetry(transf_nodes, 0);  
            transf_nodes = symmetry(transf_nodes, 1);  
    end

    transf_nodes = rotate_vertices(transf_nodes, x(3));
    transf_nodes = translate_vertices(transf_nodes, x(1), x(2));
    final_pos = transf_nodes;
    
    aux = size(transf_nodes);
    m = aux(1);
    
    final_aux = zeros(1,2*n+2);
    final_aux(1:2) = [validdata(j,1), validdata(j,2)];
    
    for l = 1:m
        final_aux(2*l+1 : 2*l+2) = transf_nodes(l,:);
    end   
    final_results(j-1,:) = final_aux;
    
    % Error computation.
    init_error = 0;
    final_error = 0;
    for k = 0:n-1
        init_error = init_error + haversine(sgps_pos(k+1, 1), sgps_pos(k+1, 2), realpos(k+1, 1),  realpos(k+1, 2));
        final_error = final_error + haversine( final_pos(k+1, 1), final_pos(k+1, 2), realpos(k+1, 1),  realpos(k+1, 2));
    end

    disp(sprintf('Initial error: %f', init_error));
    disp(sprintf('Final error:   %f', final_error));

    final_scores(j-1,:) = [init_error, final_error];

end


%% Showing results.
transf_nodes = nodes;
switch symm
    case 2
        transf_nodes = symmetry(transf_nodes, 0);  
    case 3
        transf_nodes = symmetry(transf_nodes, 1);  
    case 4
        transf_nodes = symmetry(transf_nodes, 0);  
        transf_nodes = symmetry(transf_nodes, 1);  
end

transf_nodes = rotate_vertices(transf_nodes, x(3));
transf_nodes = translate_vertices(transf_nodes, x(1), x(2));

% Create figure and axes.
figure1 = figure;
axes1 = axes('Parent',figure1);
hold(axes1,'all');
% World plot.
%geoshow('landareas.shp', 'FaceColor', [0.5 1.0 0.5]);
%hold on;
title('Results');
scatter(realpos(:,1), realpos(:,2), 'rx', 'Parent', axes1, 'DisplayName','Real location');
hold on;
scatter(sgps_pos(:,1), sgps_pos(:,2), 'bo', 'Parent', axes1,'DisplayName','SGPS location');
scatter(transf_nodes(:,1),transf_nodes(:,2), 'b.', 'Parent', axes1, 'DisplayName', 'SGPS-WSN location');
% Create legend
legend1 = legend(axes1,'show');
set(legend1,'Orientation','horizontal','Location','NorthOutside');

init_error = 0;
final_error = 0;
for k = 0:n-1
    init_error = init_error + haversine(sgps_pos(k+1, 1), sgps_pos(k+1, 2), realpos(k+1, 1),  realpos(k+1, 2));
    final_error = final_error + haversine( final_pos(k+1, 1), final_pos(k+1, 2), realpos(k+1, 1),  realpos(k+1, 2));
end


disp(sprintf('Initial error: %f', init_error));
disp(sprintf('Final error:   %f', final_error));
