/*
 * astroalg.cpp
 * Interface to the Astronomical Algorithms and Formulas.
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
#define MIN2HOUR 24.0f/1440.0f
#define DEG2RAD  M_PI/180.f

#include <cmath>
#include "../include/astroalg.h"

#include <iostream> //For debug purposes
using namespace std;

AstroAlg::AstroAlg() {

}

AstroAlg::~AstroAlg() {
}

float AstroAlg::calcFracYear (const unsigned int nday) {
	return 2.f*M_PI/365.f*(nday);
}

float AstroAlg::equationOfTime (const float beta) {
	 return MIN2HOUR*229.18*(0.000075 + 0.001868*cos(beta) - 0.032077*sin(beta) - 0.014615*cos(2*beta) - 0.040849*sin(2*beta));
}

float AstroAlg::equationOfTime (const unsigned int nday) {
	float beta = calcFracYear(nday);
	return equationOfTime(beta);
}

float AstroAlg::calcLongitude (const float midDay) {
	return (180.f/12.f*(12-midDay));
}

//TODO: Improve this calculation by using gradient descent or something like that.
float AstroAlg::calcLatitude (const float delta, const float asunset) {
	float min_error = 10000;
	float best_lat;
	for (float latitude = -90; latitude <= 90; latitude += 0.1) { //Numerically solving the accurate latitude formula.
		float error_now = fabs(((sin(-0.83*DEG2RAD)-sin(latitude*DEG2RAD)*sin(delta))/(cos(latitude*DEG2RAD)*cos(delta))) - cos(asunset));
		if (error_now < min_error) {
			min_error = error_now;
			best_lat = latitude;
			//cout << "Best Latitude found: " << latitude << endl;
		}
	}
	return best_lat;
}

float AstroAlg::sunDeclination (const float beta) {
	 return 0.006918f-0.399912f*cos(beta)+0.070257f*sin(beta)-0.006758f*cos(beta*2)+0.000907f*sin(beta*2)-0.002697f*cos(beta*3)+0.00148f*sin(beta*3);
}

float AstroAlg::sunDeclination  (const unsigned int nday) {
	float beta = calcFracYear(nday);
	return sunDeclination(beta);
}

float AstroAlg::angularSunset (const float ss, const float midDay) {
	return M_PI/12.f*fabs(ss-midDay);
}
