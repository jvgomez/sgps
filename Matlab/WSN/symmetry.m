function [symm] = symmetry (vertices, axis)

% Axis: 0 -> x
%       1 -> y

if axis == 0
    for i = 1 : length(vertices)
        symm(i,:) = [vertices(i,1), -vertices(i,2)];
    end
    
elseif axis == 1
    for i = 1 : length(vertices)
        symm(i,:) = [-vertices(i,1), vertices(i,2)];
    end
    
end