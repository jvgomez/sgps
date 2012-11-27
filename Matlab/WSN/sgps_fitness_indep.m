function F = sgps_fitness_indep(cit, eval)
% cit = [long1 lat1 long2 lat2...]
aux = size(eval.sgps_pos);
n = aux(1);

test_pos = reshape(cit,2,n)';
% Distances among sensors in the DE population member.
for i = 1:n
    for j = i:n
        % We need to add noise here.
        D_de(i,j) = haversine(test_pos(i,1), test_pos(i,2), test_pos(j,1), test_pos(j,2));
    end
end

sat_dnodes = 10000;
d_nodes = sum(sum(abs(eval.D - D_de))); % Real - algorithm.
d_nodes = d_nodes*100/sat_dnodes; %Saturating WSN error at 10000.

% Mahalanobis distance with respect the initial SGPS position.
% Maybe mahalanobis distance is not the best, maybe it is better to use the
% gaussian value to allow to move the solution far away from the inital SGPS position.
d_mah = 0;
sat_mah = 10;
for i = 1:n
    aux = mah_dist(test_pos(i,:), eval.sgps_pos(i,:), eval.mu, eval.SIGMA );
%     if aux > sat_mah 
%         aux = sat_mah;
%     end
    d_mah = d_mah + aux*100/sat_mah; %Saturating mahalanobis at sat_mah.
    %d_mah = d_mah + mah_dist(test_pos(i,:), eval.sgps_pos(i,:), eval.mu, eval.SIGMA );
end

% d_mod = 0;
% for i = 1:n
%     d_mod = d_mod + haversine(test_pos(i,1), test_pos(i,2), eval.sgps_pos(j,1), eval.sgps_pos(j,2));
% end

% To minimize:
F = eval.alpha*d_nodes + (1-eval.alpha)*d_mah;
%F = eval.alpha*d_nodes + (1-eval.alpha)*d_mod;