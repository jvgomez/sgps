%  Part of the SGPS Project. http://www.sgpsproject.org
%  Copyright (C) 2012 Javier V. Gómez
%
%  This program is free software: you can redistribute it and/or modify
%  it under the terms of the GNU General Public License as published by
%  the Free Software Foundation, either version 3 of the License, or
%  (at your option) any later version.
%  This program is distributed in the hope that it will be useful,
%  but WITHOUT ANY WARRANTY; without even the implied warranty of
%  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
%  GNU General Public License for more details.
%  You should have received a copy of the GNU General Public License
%  along with this program.  If not, see <http://www.gnu.org/licenses/>.

function [p1, p2] = random_elements(n_elements)
%Monte-Carlo random generation
v = 1:n_elements;
weight = 1./(1.05.^v);
weight = weight / sum(weight); 
cdf = cumsum(weight); 
random = rand(1,1);
p1 = find (cdf >= random, 1, 'first');
random = rand(1,1);
p2 = find (cdf >= random, 1, 'first');