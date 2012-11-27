/*
 * noaafile.cpp
 * Specific NOAA File Class.
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
#include <fstream>
#include <string>
#include <cmath>
#include "../include/noaafile.h"
#include "../include/coordinates.h"

using namespace std;
using namespace boost::filesystem;

NOAAFile::NOAAFile() {
	threshold = 0.0f;
}

NOAAFile::NOAAFile (const path p)
{
	name  = p.filename();
	ppath = p.string();
	size  = file_size(p);
	threshold = 0.0f;
}

NOAAFile::~NOAAFile() {

}

void NOAAFile::info () const {
	cout << "NOAA file: " << name << endl;
}

Day NOAAFile::read() {
	cout << "Reading NOAA file " << ppath << endl;

	Day d;
	fstream stored;

	vector <float> times;
	vector <float> values;

	stored.open(ppath.c_str(), fstream::in);

	if (stored.good()) {
		//TODO: Improve these lines with "getline" command. Much easier to understand.

		//This value says if the measure is OK.
		int error_flag = 0;
		//The file pointer is moved to the coordinates position.
		char station_name[30];
		stored.getline(station_name, 30);
		string s(station_name);
		d.setStation(s);

		float latitude, longitude;
		stored >> latitude >> longitude;
		Coordinates c;
		c.latitude = latitude;
		c.longitude = longitude;
		d.setRealCoordinates(c);

		//The file pointer is moved to the year position.
		int year;
		stored.seekp(18, ios::cur);
		stored >> year;
		d.setYear(year);

		//The file pointer is moved to the day position.
		int day;
		stored>>day;
		d.setDay(day);

		//Returning to the beginning of the line to start gathering data.
		stored.seekp(-9, ios::cur);
		float auxtime;
		float auxvalue;
		while(!stored.eof())
		{
			//Reading the time of the measure.
			stored.seekp(23, ios::cur);
			stored >> auxtime;
			times.push_back(auxtime);

			//Reading the value of the measure.
			stored.seekp(8, ios::cur);
			stored >> auxvalue;
			stored >> error_flag;

			//TODO: include the skipfile with the logger.
			//if(error_flag != 0)
			//	skip = 4;

			values.push_back(auxvalue);

			//Moving the pointer to the end of the line.
			stored.seekp(190, ios::cur);
		}
		stored.close();
	}
	else
		cout << "File not found: " << ppath << endl;

	//Due the way of reading the data, one more line is read. It is erased here.
	times.pop_back();
	values.pop_back();

	cout << d.getStation() << " " << d.getRealCoordinates().latitude << " " << d.getRealCoordinates().longitude <<" day info: " << d.getDay() << " " << d.getYear() << "Measures taken: " << values.size() << endl;

	transitions = getTransitions(values);
	d.setTransitions(transitions);
	float sunrise = findSunrise(times, values);
	float sunset = findSunset(times, values);
	d.setSunrise(sunrise);
	d.setSunset(sunset);
	return d;
}

float NOAAFile::findSunrise(const vector<float> & times, const vector<float> & values) {

	for(int i=1;i<values.size()-2;i++) {
		if ((values[i+1]>=threshold) && (values[i]>=threshold) && (values[i-1]<threshold)) {
			//TODO: In the paper version this if was transitions = 2, so it always entered here. Test new algorithms to find sunrise and sunset.
			//TODO: This is as in version 1.6.1. Fix this if.
			if (transitions = 2) {
				if (values[i] == threshold)
					return times[i];
				return (times[i]+times[i-1])/2.0f;
			}
			int  transition1 = i;
			int  transition2 = i;
			bool bestSR 	 = false;

			if (transitions > 2) {

				int aux = values.size() - 2;
				int positiveMeasure = 0;

				for ( int j = i + 1; j < aux; j++) {

					if ( (values[j + 1] < threshold) && (values[j] >= threshold) ) {
						transition2 = transition1;
						transition1 = j;
					}
					if ( (values[j] <= threshold) && (values[j+1] > threshold) ) {
						transition2 = transition1;
						transition1 = j;
					}

					if (values[j] > threshold) positiveMeasure += 1;
					if (values[j] < threshold) {
						positiveMeasure = 0;
					}

					if (positiveMeasure > 20) { //if there are too many positive measures, for is finished. (
						bestSR = true;
						j = aux;
					}

					if ( (j == 1) && (positiveMeasure > 5) )
						bestSR = true;
				}
			}
			if  (bestSR)
				return (( times[transition2] + times[transition1]) / 2.0f);
			else
				return -1; // SR not found.
		}
	}
	//TODO: distinguish between the previous return -1 and this one.
	return -1; //If error occurs.
}

float NOAAFile::findSunset(const vector<float> & times, const vector<float> & values) {
	for(int i=values.size()-2;i>0;i--)	{
		if ((values[i+1]<threshold) && (values[i]>=threshold) && (values[i-1]>threshold))
		{
			if (transitions == 2) {
				if (values[i] == threshold)
					return times[i];
				return (times[i-1] + times[i])/2.0f;
			}
			bool bestSS 	 = false;
			int  transition1 = i;
			int  transition2 = i;

			if (transitions > 2) {
				int positiveMeasure = 1;
				for (	int j = i; j > 0; j--) {

					if ( (values[j - 1] < threshold) && (values[j] >= threshold) ) {
						transition2 = transition1;
						transition1 = j;
					}
					if ( (values[j] <= threshold) && (values[j - 1] > threshold) ) {
						transition2 = transition1;
						transition1 = j;
					}
					if (values[j] > threshold) positiveMeasure += 1;

					if (values[j] < threshold) {
						positiveMeasure = 0;
					}

					if (positiveMeasure > 20) { //if there are too many positive measures, for is finished.
						bestSS = true;
						j = 0;
					}
					if ( (j == 0) && (positiveMeasure > 5) )
						bestSS = true;
				}
			}
			if (bestSS)
				return (( times[transition2] + times[transition1]) / 2.0f);
			else
				return -1; // SS not found.
		}
	}
	//TODO: distinguish between the previous return -1 and this one.
	return -1; //If error occurs.
}

//This function exist because more than 2 transitions in NOAA is still a problem.
unsigned int NOAAFile::getTransitions(const vector<float> & values) {
	int trans = 0;
	//If the sign of this number and the previous are different, a transition has occurred.
	float sign = 0.0;
	float sign_prev = 0.0;
	for(unsigned int i=1; i<values.size(); i++) {
		sign = copysignf(1.0,values[i]);
		sign_prev = copysignf(1.0,values[i-1]);
		if (sign != sign_prev)
			trans++;
	}
	return trans;
}
