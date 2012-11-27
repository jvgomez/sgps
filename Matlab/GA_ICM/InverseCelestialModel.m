% This file runs the Inverse Celestial Model but using and optimization
% technique (Genetic Algorithm) to find the best coordinates for a given
% sunrise, sunset and date (read from file).
%
% Data is a matrix with 6 column vectors:
%   Data(1,:) = day (from 1 to 365 or 366.)
%   Data(2,:) = year.
%   Data(3,:) = Measured sunrise.
%   Data(4,:) = Measured sunset.
%   Data(5,:) = Real latitude.
%   Data(6,:) = Real longitude.

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


clear all;
close all;

fid = fopen('Data1.txt');
%fid = fopen('Data2-MoreTransitions.txt');
k = 0;
lat_e = [];
long_e = [];
fitness = [];

while ~feof(fid)
    k = k+1;
    str = ['File: ' num2str(k)];
    disp(str);
    data = fscanf(fid, '%u %u %f %f %f %f',6);
    [lat long fit] = genetic_algorithm(data(3), data(4), data(2), data(1));
    fitness(k) = fit;
    lat_e(k) = data(5) - lat;
    long_e(k) = data(6) - long;
    
%     if(mod(k,10)==0)
%         figure(1)
%         scatter(long_e,lat_e,'b.')
%     end
end