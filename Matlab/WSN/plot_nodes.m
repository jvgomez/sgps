function plot_nodes (nodes)

hold on;

% Base node.
plot(nodes(1,1) ,nodes(1,2),'gx','MarkerSize', 10, 'LineWidth', 2);

for i = 1 : length(nodes)-1
    plot(nodes(i+1,1) ,nodes(i+1,2),'rx','MarkerSize', 10, 'LineWidth', 2);
    line([nodes(i,1) nodes(i+1,1)],[nodes(i,2) nodes(i+1,2)]);   
end

% Adding the last line of the polygon.
line([nodes(1,1) nodes(end,1)],[nodes(1,2) nodes(end,2)]);

hold off;