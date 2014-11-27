/*
 * options.cpp
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



#include <string>
#include <iostream>

#include "../include/options.h"

using namespace std;
Options * Options::instance_ = 0;	// Pointer initialised to 0.

Options * Options::Instance () {
    if (instance_ == 0) {			// First call to this class?
        instance_ = new Options; 	// If yes, we instantiate the class.
        //atexit(&destroyOptions);
    }

    return instance_;
}


Options::Options() {

}

void Options::addFileType(const string &s) {
    if (!isFileType(s)) //Check that is not already included.
        fileTypes_.push_back(s);
}


bool Options::isFileType(const string &s) {
    for (vector<string>::iterator it (fileTypes_.begin()); it != fileTypes_.end(); ++it) {
        if (it->compare(s) == 0)
            return true;
    }

    return false;
}


