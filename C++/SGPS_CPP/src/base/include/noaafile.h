/*
 * noaafile.h
 * Specific NOAA File Class.
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

#ifndef NOAAFILE_H_
#define NOAAFILE_H_

#include <vector>
#include "file.h"


class NOAAFile: public File {
public:
	NOAAFile();
	NOAAFile(const boost::filesystem::path);
	virtual ~NOAAFile();
	//TODO: change ::info method by << operator: cout<<day;
	void info () const;
	
	/**
	 * Reads the file getting all the desired parameters into a Day class.
	 * @param saveData true: will save the times and light vectors into the Day class (this consumes lots of memory, use
	 * only when necessary.
	 * 
	 * @return a Day instance containing all the information required for that day.
	 * */
	 
	Day read (bool saveData = false);
	float findSunrise(const std::vector<float> &, const std::vector<float> &);
	float findSunset(const std::vector<float> &, const std::vector<float> &);

	unsigned int getTransitions(const std::vector<float> &);

	inline void setThreshold (const float t)	{threshold = t;}
	inline float getThreshold() const			{return threshold;}
	
	

private:
	unsigned int transitions;
	float threshold;
};

#endif /* NOAAFILE_H_ */
