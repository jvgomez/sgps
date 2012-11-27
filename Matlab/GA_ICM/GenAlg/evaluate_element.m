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

function fitness = evaluate_element(lat, long, mSR, mSS, y, month, day)

n_elements = length(lat);

for i = 1:n_elements
	[SR SS] = IterativeFCM(lat(i), long(i), y, month, day);
    %The highest difference is penalized. Not both taking into account to
    %avoid big differences on the error of sunrise and sunset
    if abs(SR-mSR) > abs(SS-mSS)
        fitness(i) = abs(SR-mSR);
    else
        fitness(i) = abs(SS-mSS);
    end
end;