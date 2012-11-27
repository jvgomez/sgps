clear all;
close all;
%% Planteamiento: configurando el nodo 1 en [0,0] el nodo 2 en [d12,0],
%%obtener la posicion relativa de todos los demas nodos a traves de
%%tri�ngulos y añadiendo una restriccion para resolver las dos posibles
%%localizaciones de los tri�ngulos. Finalmente, se obtienen las posiciones
%%relativas de todos los nodos.

%%Luego, rotar y transladar hasta conseguir el mejor fitness. Haria falta
%%meter escalas horitonzales y verticales? Yo creo que si, aunque se puede
%%evitar confiando en las posiciones iniciales dadas por SGPS.
n = 5; % Number of vertices.

% Distances always named first with the lowest number of stations.
D = zeros(n,n); % Matrix of distances.
D(1,2) = 1;  % Automatically acquired from RF distance measuring.
D(1,3) = 1.6;
D(1,4) = 0.7;
D(2,3) = 1.4;
D(2,4) = 1.5;
D(3,4) = 1.2;

D(1,5) = 1;
D(2,5) = 1.5;
D(4,5) = 1;

%% First iteration.
vertices  = solve_triangle_SSS(D(1,2), D(1,3), D(2,3));

%% Rest of iterations.
for i = 2 : n-2
    vert_aux = solve_triangle_SSS(D(1,2), D(1,i+2) , D(2,i+2) , vertices(end,:), D(i+1, i+2)); % Last two parameters: restrictions.
    vertices(i+2,:) = vert_aux(3,:);
end  

%% Plotting the polygon.
figure; hold on;
plot_nodes(vertices);
% for i = 1 : n-1
%     plot(vertices(i,1) ,vertices(i,2),'rx','MarkerSize', 10, 'LineWidth', 2);
%     line([vertices(i,1) vertices(i+1,1)],[vertices(i,2) vertices(i+1,2)]);   
% end
% 
%     % Adding the last line of the polygon.
% plot(vertices(n,1) ,vertices(n,2),'gx','MarkerSize', 10, 'LineWidth', 2);
% line([vertices(1,1) vertices(n,1)],[vertices(1,2) vertices(n,2)]);

%% Displaying some information.
disp('Matrix of real distances:');
str = [];
for i = 1:n
    for j = i:n
        D_real(i,j) = euc_dist(vertices(i,:)', vertices(j,:)');
    end
end
disp(D_real);

disp('Errors on the distances:');
disp(D-D_real);

% All operations are implemented with respect (0,0), so translate should be
% the last transformation.
figure;
subplot(2,2,1)
translated = symmetry(vertices, 0);
plot_nodes (translated);
subplot(2,2,2)
translated = symmetry(translated, 1);
plot_nodes (translated);
subplot(2,2,3)
rotated = rotate_vertices(translated, pi/2);
plot_nodes (rotated);
subplot(2,2,4)
translated = translate_vertices(rotated,2,2);
plot_nodes (translated);