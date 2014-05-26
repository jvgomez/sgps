/*
 * huefile.h
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


#ifndef HUEFILE_H_
#define HUEFILE_H_


#include <vector>
#include <boost/algorithm/string.hpp>
#include <boost/filesystem.hpp>
#include "day.h"
#include "file.h"



class HUEFile: public File {
public:
	HUEFile();
	HUEFile(const boost::filesystem::path);
	virtual ~HUEFile();
	
	void info () const;
	
	
	Day read (bool saveData = false);
	
	
	
private:
	
	int elevation;
	int column;
	
};

#endif /* HUEFILE_H_ */
