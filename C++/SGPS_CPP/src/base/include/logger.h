/*
 * logger.h
 * Helper class to log results data.
 * Part of the SGPS Project. http://www.sgpsproject.org
 * Copyright (C) 2012 Javier V. Gómez, Isaac Rivero
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

#ifndef LOGGER_H_
#define LOGGER_H_


#include <boost/algorithm/string.hpp>
#include "coordinates.h"
#include "sgps.h"
#include "options.h"
#include "day.h"


class Logger {
	
public:

	Logger();
	virtual ~Logger();
	
	
	/**
	 * Method to iniciated files to save th program's parametres
	 * */
	static void startFiles();
	/**
	 * Method to save coordinates in a file
	 * @param c coordinates calculated in the program.
	 * */
	static void printCoordinates(const Coordinates);
	
	/**
	 * Method to save place information in a file
	 * @param d place information
	 * @param measures number of measures.
	 * */
	static void placeInfo(Day &d, const int measures);
	
	/**
	 * Method to save valid files in other file
	 * @param name file name
	 * @param ppath file path.
	 * */
	static void validFiles(const std::string name, const std::string ppath, const int skipFile, const Day &);
	
	/**
	 * Method to save invalid files in other file
	 * @param name file name
	 * @param ppath file path
	 * @param invalid the reason of invalid file.
	 * */
	static void invalidFiles(const std::string name, const std::string ppath, const int skipFile);
	
	/**
	 * Method to save error in coordinates calculated in a file
	 * @param realCoord coordinates real
	 * @param sgpsCoord coordiantes calculated in the program
	 * @param error subtraction of realCoord and sgpsCoord.
	 * */
	static void errorCoord (const Coordinates realCoord, const Coordinates sgpsCoord, const Coordinates errorDegree, const float errorKm1, const Coordinates errorKm2, const Coordinates errorPercent, const std::string station, const int day, const int year);

	/**
	 * Method to save all information of the station
	 * @param d place information
	 * */
	static void all(Day &d);
	

	


};

#endif /* LOGGER_H_ */
