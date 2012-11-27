function [vertices] = solve_triangle_SSS (d12, d13, d23, prest, drest)

alpha1 = acos( (d12^2 + d13^2 - d23^2) / (2*d12*d13) );
alpha2 = acos( (d12^2 + d23^2 - d13^2) / (2*d12*d23) );
%alpha3 = pi - alpha1 - alpha2; % Not necessary

vertices(1,:) = [0 0];  % Assuming that the line 1-2 is horizontal.
vertices(2,:) = [d12 0];

if nargin == 5
    daux1 = euc_dist([vertices(2,1) + d23*cos(pi-alpha2), vertices(2,2) + d23*sin(pi-alpha2)]', prest');
    daux2 = euc_dist([vertices(2,1) + d23*cos(pi+alpha2), vertices(2,2) + d23*sin(pi+alpha2)]', prest');
    
    dif1 = abs(drest-daux1);
    dif2 = abs(drest-daux2);
    
    if dif1 > dif2
        alpha2 = -alpha2;
    end
    
end

vertices(3,:) = [vertices(2,1) + d23*cos(pi-alpha2), vertices(2,2) + d23*sin(pi-alpha2)];
