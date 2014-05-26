/*
 * astroalg.h
 * Interface to the Astronomical Algorithms and Formulas.
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

#ifndef ASTROALG_H_
#define ASTROALG_H_

#include "coordinates.h"

class AstroAlg {
public:
	AstroAlg();
	virtual ~AstroAlg();
	//Result in radians.
	static float calcFracYear (const unsigned int); //Beta in the papers.
	//Results in hours.
	static float equationOfTime (const float); 			//EqT in the papers.
	static float equationOfTime (const unsigned int);   //EqT in the papers.
	//Result in radians.
	static float calcLongitude (const float);
	static float calcLatitude (const float, const float);
	//TODO: include the fast latitude formula.
	//Result in radians.
	static float sunDeclination (const float); 			 //Delta in the papers.
	static float sunDeclination (const unsigned  int);   //Delta in the papers.
	//Result in radians.
	static float angularSunset (const float, const float); //a_sunset in the papers.
	
	
	/**
	 * Method to get error in degrees
	 * @param realCoord coordinates real
	 * @param sgpsCoord coordiantes calculated in the program
	 * */
	static Coordinates errorDeg (const Coordinates &, const Coordinates &);
	
	/**
	 * Method to get error in km with haversine method
	 * @param realCoord coordinates real
	 * @param sgpsCoord coordiantes calculated in the program
	 * @param errorDegree error in degrees
	 * */
	static float errorHaversine (const Coordinates &, const Coordinates &, const Coordinates &);
	
	/**
	 * Method to get error in km
	 * @param realCoord coordinates real
	 * @param sgpsCoord coordiantes calculated in the program
	 * @param errorDegree error in degrees
	 * */
	static Coordinates errorKm (const Coordinates &, const Coordinates &, const Coordinates &);
	
	/**
	 * Method to get error in percentage
	 * @param errorDegree error in degrees
	 * */
	static Coordinates errorPerc (const Coordinates &);
	
	


private:

};

#endif /* ASTROALG_H_ */
