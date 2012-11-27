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

#include <boost/filesystem.hpp>

#include "diranalyzer.h"
#include "celestialmodel.h"
#include "logger.h"
#include "day.h"
#include "coordinates.h"

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

private:
	DirAnalyzer    		dirAnalyzer;
	//CelestialModel 	basicModel;
	Logger         		log;
	std::vector<Day> 	days;
	std::vector<Coordinates> coords;

};

#endif /* SGPS_H_ */
