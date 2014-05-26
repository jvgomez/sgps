/*
 * plotter.h
 * Helper class to log results data.
 * Part of the SGPS Project. http://www.sgpsproject.org
 * Copyright (C) 2013 Javier V. Gómez, Isaac Rivero
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef PLOTTER_H_
#define PLOTTER_H_




#include <iostream>
#include "coordinates.h"
#include "gnuplot_i.h"




class Plotter {
public:
	//Plotter();
	Plotter(const bool &w);
	virtual ~Plotter();
	
	
	/**
	 * Method to plot SGPS Coordinates
	 * @param c SGPS Coordinates
	 * @param station name of station
	 * */
	void plotCoordinates (const Coordinates c, std::string station);
	
	/**
	 * Method to wait before of close the plot
	 * */
	static void wait_for_key();
	Gnuplot getG1()const							{return g1;}
	
	/**
	 * Method to plot world map
	 * */
	void world ()							{g1.cmd ("plot '../data/world.dat' with lines linestyle 1");}
	
	static void plotDay (const std::vector<float> &, const std::vector<float> &, const int day, const int year);

	
	
	

private:

	Gnuplot g1;

};

#endif /* PLOTTER_H_ */
