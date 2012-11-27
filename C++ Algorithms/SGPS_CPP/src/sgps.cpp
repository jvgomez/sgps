/*
 * sgps.cpp
 * Main SGPS Class' body. This is the starting point.
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

#include "../include/sgps.h"
#include <iostream>


using namespace std;
using namespace boost::filesystem;

SGPS::SGPS() {

}

SGPS::~SGPS() {
}

void SGPS::readFolder(const path folder_path) {
	dirAnalyzer.extractValidFiles(folder_path);
	dirAnalyzer.info();
}

void SGPS::readFiles () {
	days = dirAnalyzer.readFiles();
}


void SGPS::getCoordinates(){
	for (vector<Day>::iterator it (days.begin()); it != days.end(); ++it) {
		Coordinates c = CelestialModel::ForwardCelestialModel(*it);
		cout << "---------- Latitude: " << c.latitude << " ---------- Longitude: " << c.longitude << endl;

	}
}

Coordinates SGPS::getCoordinates(Day &) {

}
