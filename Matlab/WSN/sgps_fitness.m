function F = sgps_fitness(cit, eval)

% cit(1) = ploygon x translation (longitudes);
% cit(2) = ploygon y translation (latitudes);
% cit(3) = ploygon theta rotation (radians);

nodes = eval.nodes;
sgps_pos = eval.sgps_pos;

transf_nodes = rotate_vertices(nodes, cit(3));
transf_nodes = translate_vertices(transf_nodes, cit(1), cit(2));

aux = size(nodes);
n = aux(1);

F = 0;
for i = 1:n
    %F = F + euc_dist(transf_nodes(i,:)', sgps_pos(i,:)');
    F = F + mah_dist(transf_nodes(i,:), sgps_pos(i,:), eval.mu, eval.SIGMA );
end