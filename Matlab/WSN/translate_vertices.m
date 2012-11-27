function [translated] = translate_vertices(vertices, x, y)

for i = 1 : length(vertices)
    translated(i,:) = vertices(i,:) + [x y];
end