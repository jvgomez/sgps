%  Iterative Forward Celestial Model
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

function [SR SS] = IterativeFCM(lat, long, y, mo, d) 

[SR SS] = ForwardCelestialModel(lat, long, y, mo, d);
[SRh SRm SRs] = HHMMSS(SR);
[SR ~] = ForwardCelestialModel(lat, long, y, mo, d, SRh, SRm, SRs);

[SSh SSm SSs] = HHMMSS(SS);
[SR2 SS] = ForwardCelestialModel(lat, long, y, mo, d, SSh, SSm, SSs);

