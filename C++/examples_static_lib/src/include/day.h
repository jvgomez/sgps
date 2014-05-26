/*
 * day.h
 * Main data class. Encapsulates all the information for one day.
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

#ifndef DAY_H_
#define DAY_H_

#include <vector>
#include <boost/algorithm/string.hpp>
#include "coordinates.h"


class File; //Forward declaration to avoid cyclic dependencies.

class Day {
public:
	Day();
	virtual ~Day();

	//TODO: recieve references instead of parameters to improve performance.
	inline void setDay(const unsigned int d)     					{nday = d;}
	inline void setYear(const unsigned int y)    					{year = y;}
	inline void setTransitions(const unsigned int t)    			{transitions = t;}
	inline void setSunrise(const float sr) 							{sunrise = sr;}
	inline void setSunset(const float ss)  							{sunset = ss;}
	inline void setRealCoordinates(const Coordinates c)				{realCoord.latitude = c.latitude;
																	 realCoord.longitude = c.longitude;}
																	 
	
	/**
	 * Method to save c in the private variable sgpsCoord
	 * @param c coordiantes calculated in the program
	 * */
	inline void setSGPSCoordinates(const Coordinates c)				{sgpsCoord.latitude = c.latitude;
																	 sgpsCoord.longitude = c.longitude;
																	 }
	
	
	//inline void setRealCoord(const float lat , const float lon)		{rLatitude = lat;
	//																 rLongitude = lon;}
	inline void setStation(const std::string s) 					{station = s;}
	inline void setFile(File* f)									{file = f;}
	
	/**
	 * Method to save the times vector of this day.
	 * @param t times vector.
	 * */
	void setTimes(const std::vector<float> t)						{times_ = t;}
		
	/**
	 * Method to save the light intensities vector of this day.
	 * @param v light intensities vector.
	 * */
	void setValues(const std::vector<float> v)						{values_ = v;}


	inline unsigned int getDay() const   			{return nday;}
	inline unsigned int getYear() const  			{return year;}
	inline unsigned int getTransitions() const   	{return transitions;}
	inline float getSunrise() const					{return sunrise;}
	inline float getSunset() const 					{return sunset;}
	//inline float getRealLatitude() const			{return rLatitude;}
	//inline float getRealLongitude() const			{return rLongitude;}
	inline Coordinates getRealCoordinates () const  {return realCoord;}
	
	/**
	 * Method to get sgpsCoord beacause is a private variable
	 * @return sgpsCoord coordinates calculated in the program
	 * */
	inline Coordinates getSGPSCoordinates () const  {return sgpsCoord;}
	
	inline std::string getStation() const			{return station;}
	inline File* getFile() const					{return file;}

	//TODO: change ::info method by << operator: cout<<day;
	void info() const;
	
	
	/**
	 * Method to get error in coordinates calculated
	 * */
	void getError();  //TODO: ¿?
	
	
	/**
	 * Method to get sgpsCoord beacause is a private variable
	 * @return errorDegree error in Coordiantes calculated in the program
	 * */
	inline Coordinates getErrorDegree() const  			{return errorDegree;}
	/**
	 * Method to get sgpsCoord beacause is a private variable
	 * @return errorKm1 error in km in Coordiantes calculated in the program with haversine method
	 * */
	inline float getErrorHaversine() const  			{return errorKm1;}
	/**
	 * Method to get sgpsCoord beacause is a private variable
	 * @return errorkm2 error km in Coordiantes calculated in the program
	 * */
	inline Coordinates getErrorKm() const  				{return errorKm2;}
	/**
	 * Method to get sgpsCoord beacause is a private variable
	 * @return errorPercent error in percentage in Coordiantes calculated in the program
	 * */
	inline Coordinates getErrorPercent() const  		{return errorPercent;}
	
	
	/**
	 * Method to get the times vector in this day.
	 * @return vector containing the times.
	 * */
	std::vector<float> getTimes() const					{return times_;}
	
	/**
	 * Method to get the light intensities vector in this day.
	 * @return vector containing the light intensities.
	 * */
	std::vector<float> getValues() const				{return values_;}	
	
	/**
	 * Method to know the information that the user wants see
	 * @param argc number of parameters that you pass to program
	 * @param argv array with the parameters that you pass to program
	 * */
	void plotDay ();
		

private:
	File* file; //TODO: set in dirAnalyzer.cpp Test if this works ok.
	unsigned int nday;
	unsigned int year;
	unsigned int transitions;
	float sunrise;
	float sunset;
	Coordinates realCoord;
	Coordinates sgpsCoord;
	Coordinates errorDegree;
	float errorKm1;
	Coordinates errorKm2;
	Coordinates errorPercent;
	std::string station; //TODO: for a better design, station should be a class, with coordinates and elevation.
	//There is not a vector to store measurements to avoid innecesary data. Add if needed.
	
	std::vector <float> times_;
	std::vector <float> values_;
};

#endif /* DAY_H_ */
