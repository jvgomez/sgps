%  Main function of the Genetic Algorithm.
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

function [lat long fit] = genetic_algorithm(mSR, mSS, y, d)
tic()
n_elements = 200; %Population size.
n_parameters = 2; %Parameters to optimize.
threshold = 0.001; %Fitness minimum threshold

[day month] = getDayMonth(d);
population = generate_initial_population(n_elements, n_parameters);
generation = 1;
convergence = 0;
evolution = [];

while ~convergence 
    
    fitness = [];
    lat = population(1,:);
    long = population(2,:);
    fitness = evaluate_element(lat, long, mSR, mSS, y, month, day);
	[~, order] = sort(fitness, 'ascend'); %Sorting from best to worst.
    new_population = zeros(n_parameters, n_elements);
    % Elitism
    new_population(:,1) = population(:,order(1));
    
    for i=2:n_elements
        [p1, p2] = random_elements(n_elements);
        new_element = crossover(population(:,order(p1)),population(:,order(p2)));
        new_population(:,i) =new_element;
    end;
    
    generation = generation + 1;
    best_element = fitness(order(1));
    evolution(end+1) = best_element;

    if(fitness(order(1)) < threshold)
        convergence = 1;
    end
%         plot(evolucion); %Plot the fitness of the best element of each
%         iteration
    population = new_population;
    pause(0.01);
end

lat = population(1,1);
long = population(2,1);
fit = fitness(order(1));
toc()