function [rotated] = rotate_vertices(vertices, theta)

% Counter clockwise rotation over (0,0) (first vertex)
% x' = x*cos(theta) + y*sin(theta)
% y' = -x*sin(theta) + y*cos(theta)
% theta in radians.

R = [cos(theta) -sin(theta);
    sin(theta) cos(theta)];

for i = 1 : length(vertices)
    rotated(i,:) = R*vertices(i,:)';
end