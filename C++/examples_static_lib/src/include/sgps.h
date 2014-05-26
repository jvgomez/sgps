/*
 * sgps.h
 * Main SGPS Class' header. This is the starting point.
 * Part of the SGPS Project. http://www.sgpsproject.org
 * Copyright (C) 2012 Javier V. Gómez
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

#ifndef SGPS_H_
#define SGPS_H_

#include <vector>
#include <boost/filesystem.hpp>

#include "diranalyzer.h"
#include "celestialmodel.h"
#include "logger.h"
#include "day.h"
#include "coordinates.h"
#include "console.h"
#include "plotter.h"



//TODO: This class could be very general, since the user cannot get information
//about what is happening in functions such as readFolder, readFiles, getCoordinates...
//Maybe the solution is to split the functions into smaller functions but increasing the
//code in the main, trying to create a PCL-like programming interface.
class SGPS {
	
public:
	SGPS();
	virtual ~SGPS();

	void readFolder(const boost::filesystem::path);
	void readFiles();

	//This function works over the vector days of the SGPS class and fills the coords vector.
	void getCoordinates();
	// This function works over one given day.
	Coordinates getCoordinates(Day &);
	
	/**
	 * Method to know the information that the user wants see
	 * @param argc number of parameters that you pass to program
	 * @param argv array with the parameters that you pass to program
	 * */
	static void parseArguments (int argc, char* argv[]);
		
		
	
	

private:
	DirAnalyzer    		dirAnalyzer;
	//CelestialModel 	basicModel;
	//Plotter plotter_;
	
	std::vector<Day> 	days;
	std::vector<Coordinates> coords;

};

#endif /* SGPS_H_ */
