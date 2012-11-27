/*
 * celestialmodel.cpp
 * Celestial Model Class' Body.
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

#include "../include/celestialmodel.h"

#include <cmath>
#include "../include/astroalg.h"

#include <iostream> //For debug purposes
using namespace std;

CelestialModel::CelestialModel() {

}

CelestialModel::~CelestialModel() {

}

Coordinates CelestialModel::ForwardCelestialModel(Day & d) {
	Coordinates c;
	float sr = d.getSunrise();
	float ss = d.getSunset();
	unsigned int nday = d.getDay();
	float midDay = (sr + ss)/2.f;

	//It is improbable to have sr == ss
	if (sr >= ss) //Fractional day
		midDay += 12.0f;
	if (midDay >= 24)
		midDay = fmod(midDay, 24);

	float EqT = AstroAlg::equationOfTime(nday);
	midDay += EqT;
	ss += EqT;

	c.longitude = AstroAlg::calcLongitude(midDay);

	float delta = AstroAlg::sunDeclination(nday);
	float a_sunset = AstroAlg::angularSunset(ss, midDay);

	c.latitude = AstroAlg::calcLatitude (delta, a_sunset);
	return c;
}

