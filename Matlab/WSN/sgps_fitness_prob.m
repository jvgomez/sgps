function F = sgps_fitness_prob(cit, eval)
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

% d_nodes = sum(sum(abs(eval.D - D_de))); % Real - algorithm.

% Mahalanobis distance with respect the initial SGPS position.
% Maybe mahalanobis distance is not the best, maybe it is better to use the
% gaussian value to allow to move the solution far away from the inital SGPS position.
d_mah = 0;
for i = 1:n
    d_mah(i) =  mah_dist(test_pos(i,:), eval.sgps_pos(i,:), eval.mu, eval.SIGMA );
end

% for i = 1:n
%     p(i) = gauss_prob(test_pos(i,:),eval.sgps_pos(i,:), eval.mu, eval.vvar);
% end

F = 0;
for i = 1:n
    for j = 1:n
        aux = 0;
        if i < j
            aux = aux + abs(eval.D(i,j) - D_de(i,j));
        elseif i > j
            aux = aux + abs(eval.D(j,i) - D_de(j,i));
        end
        F = F + aux*d_mah(i);
    end
end
