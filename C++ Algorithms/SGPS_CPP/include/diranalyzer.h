/*
 * diranalyzer.h
 * Class to obtain the files with the sunlight data.
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

#ifndef DIRANALYZER_H_
#define DIRANALYZER_H_

#include <vector>
#include <boost/filesystem.hpp>
#include "file.h"
#include "noaafile.h"
#include "day.h"

/**
 * @author Javier V. Gómez.
 *
 * Class to encapsulate directory navigation and usage based on Boost
 * libraries. Thus, it is necessary to have these libraries installed.
 *
 * This class is not 100% finished. It has only a few methods and it
 * we be improved continuously.
 * */

class DirAnalyzer {
public:
	/**
	 * Not used.
	 */
	DirAnalyzer();
	/**
	 * Not used.
	 */
	virtual ~DirAnalyzer();

	/**
	 * This method returns all the files existing in a folder and its
	 * subfolders. It is based in a depth first search.
	 *
	 * @param folder_path is the root path to start the search.
	 * @param files file structs vector in which the files data will be
	 * stored. It is originally path type, but if a char * parameter is
	 * given it will convert it automatically.
	 *
	 * @return It has no return, but the number of files read can be
	 * obtained through the size of files vector.
	 *
	 * @see readFolder()
	 */
	void getFiles(const boost::filesystem::path);

	/**
	 * Method to obtain all the items existing in a folder. This method
	 * is used by getFiles() to run a depth first search.
	 *
	 * @param p is the path of the folder it is wanted to be read.
	 *
	 * @return vector of paths (files or folders) included in the given
	 * path.
	 *
	 * @see getFiles()
	 * */
	std::vector<boost::filesystem::path> readFolder (const boost::filesystem::path);

	void extractValidFiles(const boost::filesystem::path);

	// Create new function for new type of file, and add valid files to validFiles vector (creating the own-file class).
	void getNOAAFiles();

	std::vector<Day> readFiles ();

	void info();

private:
	std::vector<File> files;
	std::vector<File*> validFiles;

};

#endif /* DIRANALYZER_H_ */
