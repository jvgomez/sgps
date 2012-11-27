% Forward Celestial Model for the Earth: it returns the sunrise and sunset
% for a given location and place.
%
% [SR, SS] = ForwardCelestialModel(lat, long, y, mo, d)
% [SR, SS] = ForwardCelestialModel(lat, long, y, mo, d, h, mi, s)
%
% Year, MOnth, Day, Hour, Minute, Second. If only the first three
% are provided a two steps algorithm is done: first the julian date
% using only default Matlab time and later, two different Julian days,
% with both times of sunrise and sunset to obtain an accurate time.
%
% This is an adaptation to Matlab of the NOAA spreadsheet.
% All the forumlas have been extracted from Astronomical Algorithms
% by Jean Meeus.

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

%% Everything is (and has to be) in degrees. Also all hours have to be in UTC.
function [SR, SS] = ForwardCelestialModel(lat, long, y, mo, d, h, mi, s)

format long;
%format
if nargin < 6
    julian_day = juliandate(y,mo,d);
else
    julian_day = juliandate(y,mo,d,h,mi,s);
end

julian_century = (julian_day - 2451545) ./ 36525;
%Geom Mean Long Sun (deg)
GMLS = rem(280.46646+julian_century.*(36000.76983 + julian_century.*0.0003032), 360);
%Geom Mean Anom Sun (deg)
GMAS = 357.52911+julian_century.*(35999.05029 - 0.0001537.*julian_century);
%Eccent Earth Orbit
%EEO = 0.016708634-julian_century*(0.000042037+0.0001537*julian_century);
%Sun Eq of Ctr
SEC = sind(GMAS).*(1.914602-julian_century.*(0.004817+0.000014.*julian_century))+sind(2.*GMAS).*(0.019993-0.000101.*julian_century)+sind(3.*GMAS).*0.000289;
%Sun True Long (deg)
STL = GMLS + SEC;
%Sun True Anom (deg)
%STA = GMAS + SEC;
%Sun Rad Vector (AUs)
%SRV = (1.000001018*(1-EEO^2))/(1+EEO*cosd(STA));
%Sun App Long (deg)
SAL = STL-0.00569-0.00478.*sind(125.04-1934.136.*julian_century);
%Mean Obliq Ecliptic (deg)
MOE = 23+(26+((21.448-julian_century.*(46.815+julian_century.*(0.00059-julian_century.*0.001813))))./60)./60;
%Obliq Corr (deg)
OC = MOE+0.00256.*cosd(125.04-1934.136.*julian_century);
%Sun Rt Ascen (deg)
%SRA = rad2deg(atan2(cosd(OC)*sind(SAL), cosd(SAL)));
%Sun Declin (deg)
SD = asind(sind(OC).*sind(SAL));
%var y
%VY = tand(OC/2)^2;
%Eq of Time (minutes)
%EqT = 4*(VY*sind(2*GMLS)-2*EEO*sind(GMAS)+4*EEO*VY*sind(GMAS)*cosd(2*I2)-0.5*VY^2*sind(4*GMLS)-1.25*EEO^2*sind(2*GMAS));
%HA Sunrise (deg)
prev = cosd(90.833)./cosd(lat).*cosd(SD)-tand(lat).*tand(SD);
if abs(prev) > 1
    disp(prev);
    disp(lat);
    pause;
end
HAS = acosd(cosd(90.833)./cosd(lat).*cosd(SD)-tand(lat).*tand(SD));
%Solar Noon (LST)
%SN = (720-4*long-EqT)/1440; %Care with the EqT.
SN = (720-4.*long)/1440; %-EqT/1440, It is +EqT so this means converted to civil time.
%Sunrise Time (LST)
SR = mod((SN-HAS.*4./1440) .* 24, 24);
%Sunset Time (LST)
SS = mod((SN+HAS.*4./1440) .* 24, 24);
