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

function new_element = crossover(element1, element2)
alpha = rand(1,1);
new_element = alpha*element1+(1-alpha)*element2;

%Mutation
mutation_probability = 0.2; %0 <= x <= 1
random = rand(1,1);
strength = 10;

if random < mutation_probability
    %If complex number appears on the FCM (HAS variable), check the limits
    %for the latitude and longitude here. This could
    pos_to_mutate = ceil(rand(1,1)*2);
    new_element(pos_to_mutate) = new_element(pos_to_mutate) + strength*(rand(1,1)-0.5); 
    
    %If the mutation exceeds the limits for the coordinates, we set it to
    %the maximum value.
    if pos_to_mutate == 1
        if abs(new_element(pos_to_mutate)) > 60
            new_element(pos_to_mutate) = sign(new_element(pos_to_mutate))*60; 
        end
    else
        if abs(new_element(pos_to_mutate)) > 180
            new_element(pos_to_mutate) = sign(new_element(pos_to_mutate))*180; 
        end
    end
end