/*
 * day.cpp
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

#include <iostream>
#include <cmath>
#include "../include/day.h"
#include "../include/logger.h"
#include "../include/astroalg.h"


using namespace std;

Day::Day() {
}

Day::~Day() {
}

void Day::info () const {
    cout <<"Day info: " << nday << " " << year << ". Transitions: " << transitions << ". Sunrise: " << sunrise <<  " Sunset: " << sunset << endl;
}


void Day::getError(){
    errorDegree = AstroAlg::errorDeg(realCoord, sgpsCoord);
    errorKm1 = AstroAlg::errorHaversine(realCoord, sgpsCoord, errorDegree);
    errorKm2 = AstroAlg::errorKm(realCoord, sgpsCoord, errorDegree);
    errorPercent = AstroAlg::errorPerc(errorDegree);

    Options * opt =  Options::Instance();
    if (opt->getLoggerOp()){
        Logger::errorCoord (realCoord, sgpsCoord, errorDegree, errorKm1, errorKm2, errorPercent, station, nday, year);
    }
}


void Day::plotDay () {
    Plotter::plotDay (times_, values_, nday, year);
}
