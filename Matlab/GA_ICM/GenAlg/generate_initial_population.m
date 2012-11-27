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

function initial_population = generate_initial_population(n_elements, n_parameters)

initial_population = rand(n_parameters,n_elements);

initial_population(1,:) = -60 + (120).*initial_population(1,:); %Latitude from -90 to 90, but if fails with very high
%latitudes values.
initial_population(2,:) = -180 + (360).*initial_population(2,:); %Longitude from -180 to 180.