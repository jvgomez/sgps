/*
 * apply.cpp
 * Main cpp file to test the SGPS code.
 * Part of the SGPS Project. http://sgpsproject.sourceforge.net/wiki/
 * Copyright (C) 2015 Javier V. Gómez
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

#include "../../base/include/sgps.h"

using namespace std;

int main (int argc, char* argv[]) {
    SGPS::parseArguments(argc, argv);
    DirAnalyzer dir;
    Day d = dir.extractDay(argv[1]);
    d.setSGPSCoordinates(CelestialModel::inverseCelestialModel(d));
    d.getError();
    
    d.info();
    
    Coordinates c = d.getErrorDegree();
    std::cout << "Degrees error: Lat " << c.latitude << "\tLong " << c.longitude << '\n'; 
    c = d.getErrorPercent();
    std::cout << "Percentage error: Lat " << c.latitude << "\tLong " << c.longitude << '\n'; 

    return 0;
}
