%% Planteamiento: configurando el nodo 1 en [0,0] el nodo 2 en [d12,0],
% obtener la posicion relativa de todos los demas nodos a traves de
% triangulos y añadiendo una restriccion para resolver las dos posibles
% localizaciones de los triangulos. Finalmente, se obtienen las posiciones
% relativas de todos los nodos.

% - Input: D, N-1xN. Distances between vertex [i,j], usually only the
%          superior triangle of the matrix is needed.


% - Output: vertices, Nx2. Relative positions between vertices. Vertex 1 
%           in [0,0] and vertex 2 in [d12 0];

function [vertices] = create_polygon (D)

aux = size(D);
n = aux(2);

% First iteration.
vertices  = solve_triangle_SSS(D(1,2), D(1,3), D(2,3));

% Rest of iterations.
for i = 2 : n-2
    vert_aux = solve_triangle_SSS(D(1,2), D(1,i+2) , D(2,i+2) , vertices(end,:), D(i+1, i+2)); % Last two parameters: restrictions.
    vertices(i+2,:) = vert_aux(3,:);
end  


% %% Displaying some information.
% %disp('Matrix of real distances:');
% str = [];
% for i = 2:n
%         D_real(1,i)   = euc_dist(vertices(1,:)', vertices(i,:)');
%         D_real(2,i)   = euc_dist(vertices(2,:)', vertices(i,:)');
%         D_real(i-1,i) = euc_dist(vertices(i-1,:)', vertices(i,:)');
% end



% disp(D_real);
% 
% disp('Errors on the distances:');
% disp(D-D_real);

% % All operations are implemented with respect (0,0), so translate should be
% % the last transformation.

% figure;
% subplot(2,2,1)
% translated = symmetry(vertices, 0);
% plot_nodes (translated);
% subplot(2,2,2)
% translated = symmetry(translated, 1);
% plot_nodes (translated);
% subplot(2,2,3)
% rotated = rotate_vertices(translated, pi/2);
% plot_nodes (rotated);
% subplot(2,2,4)
% translated = translate_vertices(rotated,2,2);
% plot_nodes (translated);