/*
 * file.h
 * Class to store file data (size, path...)
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

#ifndef FILE_H_
#define FILE_H_

#include <string>
#include <vector>
#include <boost/filesystem.hpp>
#include "day.h"

/**
 * @author Javier V. Gómez.
 *
 * Class to store the features of a file based on Boost  * libraries.
 * Thus, it is necessary to have these libraries installed.
 *
 * This class is not 100% finished. It has only a few methods and it
 * we be improved continuosly.
 * */

class File {
public:

	/**
	 * Not used.
	 * */
	File();

	/**
	 * Overload of the constructor in order to get automatically all the
	 * features of a file giving the path to the file.
	 *
	 * @param p path of the file.
	 * */
	File(const boost::filesystem::path);

	/**
	 * Not used.
	 * */
	virtual ~File();

	/**
	 * Method to set the name
	 * @param n name of the file.
	 * @see getName()
	 * */
	void setName(std::string n) 			{name=n;}

	/**
	 * Method to set the path
	 * @param p path of the file.
	 * @see getPath()
	 * */
	void setPath(std::string p) 			{ppath=p;}

	/**
	 * Method to set the size
	 * @param s size of the file.
	 * @see getSize()
	 * */
	void setSize (unsigned int s) 	{size=s;}

	/**
	 * Method to get the name of the file.
	 * @return name of the file as a string.
	 * @see setName()
	 * */
	std::string getName() const			{return name;}

	/**
	 * Method to get the path of the file.
	 * @return path of the file as a string.
	 * @see setPath()
	 * */
	std::string getPath() const			{return ppath;}

	/**
	 * Method to get the size of the file.
	 * @return size of the file in bits.
	 * @see setSize()
	 * */
	unsigned int getSize() const		{return size;}

	//TODO: change ::info method by << operator: cout<<day;
	virtual void info () const;

	virtual Day read ();

	//TODO: convert to pure virtual functions.
	virtual float findSunrise(const std::vector<float> &, const std::vector<float> &);
	virtual float findSunset(const std::vector<float> &, const std::vector<float> &);

protected:
	std::string name;
	std::string ppath; //It is ppath because path is a type of the boost filesystem.
	unsigned int size;

	//There is not a vector to store measurements to avoid innecesary data. Add if needed.
};



#endif /* FILE_H_ */
