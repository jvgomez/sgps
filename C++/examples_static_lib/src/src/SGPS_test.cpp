/*
 * SGPS_test.cpp
 * Main cpp file to test the SGPS code.
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

#include <iostream>
#include <vector>
#include <boost/progress.hpp>

#include "sgps.h"

using namespace std;

int main (int argc, char* argv[]) {

	SGPS sgps;
	
	sgps.parseArguments (argc, argv);
	
	boost::progress_timer t;

	sgps.readFolder(argv[1]);
	sgps.readFiles();
	sgps.getCoordinates();
	
	
	
	
	
	return 0;
}

