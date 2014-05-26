/*
 * logger.cpp
 * Helper class to log results data.
 * Part of the SGPS Project. http://www.sgpsproject.org
 * Copyright (C) 2012 Javier V. Gómez, Isaac Rivero
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

#include <fstream>
#include <iostream>
#include <vector>
#include <cstring>

#include "../include/logger.h"
#include "../include/diranalyzer.h"
#include "../include/options.h"





using namespace std;

Logger::Logger() {

}



Logger::~Logger() {

}



//void Logger::printCoordinates (const Coordinates c){
	
	////TODO: try to get options externally (as friend class or something)
	////without passing the arguments. What is the best solution?
	
		//string ruta2 = "coordinates";
		//string total;
	
	
		//total = DirAnalyzer::createDir(ruta2);
	
		//ofstream f;
		//f.open (total.c_str(), ios::app);
		//f << c.latitude << "\t" << c.longitude << endl;
		//f.close();
//}

void Logger::placeInfo (Day &d, const int measures){
	
		
		string ruta2 = "placeinformation";
		string total;
	
	
		total = DirAnalyzer::createDir(ruta2);
	
		ofstream p_i;
		p_i.open (total.c_str(), ios::app);
		p_i << d.getStation() << "\t" << d.getRealCoordinates().latitude << "\t" << d.getRealCoordinates().longitude <<"\t" << d.getDay() << " " << d.getYear() << "\t" << measures << "\t" << d.getTransitions() << "\t" << d.getSunrise() << "\t" << d.getSunset() << endl;
		p_i.close();

}

void Logger::startFiles(){
	
	string ruta2;
	string total;
	
	ruta2 = "placeinformation";
	total = DirAnalyzer::createDir(ruta2);
	ofstream p_i;
	p_i.open (total.c_str());
	p_i << "Place\tLatitudeReal\tLongitudeReal\tDay Year\tMeasures\tTransitions\tSunrise\tSunset\n";
	p_i.close();
	
	
	
	//ruta2 = "coordinates";
	//total = DirAnalyzer::createDir(ruta2);
	//ofstream f;
	//f.open (total.c_str());
	//f << "Latitude\tLongitude\n";
	//f.close();
	
	
	ruta2 = "validfiles";
	total = DirAnalyzer::createDir(ruta2);
	ofstream v_f;
	v_f.open (total.c_str());
	v_f << "Station\tDay\tYear\tLatitudeReal\tLongiyudeReal\tName\tPath\n";
	v_f.close();
	
	
	ruta2 = "invalidfiles";
	total = DirAnalyzer::createDir(ruta2);	
	ofstream inv_f;
	inv_f.open (total.c_str());
	inv_f << "Name\tPath\tReason\n";
	inv_f.close();
	
	ruta2 = "errorcoordinates";
	total = DirAnalyzer::createDir(ruta2);
	ofstream err;
	err.open (total.c_str());
	err << "Station\tDay\tYear\tLatitudeReal\tLongitudeReal\tLatitudeSGPS\tLongitudeSGPS\tErrorDegreeLatitude\tErrorDegreeLongitude\tErrorKm\tErrorHaversineLatitude\tErrorHaversineLongitude\tErrorPercentLatitude\tErrorPercentLongitude\n";
	err.close();
	
	ruta2 = "all";
	total = DirAnalyzer::createDir(ruta2);
	ofstream all;
	all.open (total.c_str());
	all << "Place\tDay Year\tSunrise\tSunset\tLatitudeReal\tLongitudeReal\tLatitudeSGPS\tLongitudeSGPS\tErrorDegreeLatitude\tErrorDegreeLongitude\tErrorKm\tErrorHaversineLatitude\tErrorHaversineLongitude\tErrorPercentLatitude\tErrorPercentLongitude\n";
	all.close();
	
	Options * opt =  Options::Instance();
	cout << "Output saved in: " << opt->getOutputPath() << endl;
}



void Logger::validFiles(const string name, const string ppath, const int skipFile, const Day &d){
	
		if(skipFile == 0){
			
			string ruta2 = "validfiles";
			string total;
	
	
			total = DirAnalyzer::createDir(ruta2);
	
			ofstream v_f;
			v_f.open (total.c_str(), ios::app);
			v_f << d.getStation() << "\t" << d.getDay() << "\t" << d.getYear() << "\t" << d.getRealCoordinates().latitude << "\t" << d.getRealCoordinates().longitude << "\t" << name << "\t" << ppath << endl;
			v_f.close();
		}
}



void Logger::invalidFiles(const string name, const string ppath, const int skipFile){
	
		string ruta2 = "invalidfiles";
		string total;
	
	
		total = DirAnalyzer::createDir(ruta2);
	
		ofstream inv_f;
		inv_f.open (total.c_str(), ios::app);
		inv_f << name << "\t" << ppath << "\t" << skipFile << endl;
		inv_f.close();
}


void Logger::errorCoord (const Coordinates realCoord, const Coordinates sgpsCoord, const Coordinates errorDegree, const float errorKm1, const Coordinates errorKm2, const Coordinates errorPercent, const std::string station, const int day, const int year){
	
		string path2 = "errorcoordinates";
		string total;
	
	
		total = DirAnalyzer::createDir(path2);
	
		ofstream err;
		err.open (total.c_str(), ios::app);
		err << station << "\t" << day << "\t" << year << "\t" << realCoord.latitude << "\t" << realCoord.longitude << "\t" << sgpsCoord.latitude << "\t" << sgpsCoord.longitude << "\t" << errorDegree.latitude << "\t" << errorDegree.longitude << "\t" << errorKm1 << "\t" << errorKm2.latitude << "\t" << errorKm2.longitude << "\t" << errorPercent.latitude << "\t" << errorPercent.longitude <<  endl;
		err.close();
}

void Logger::all(Day &d){
		
		string path2 = "all";
		string total;
	
	
		total = DirAnalyzer::createDir(path2);
	
		ofstream all;
		all.open (total.c_str(), ios::app);
		all << d.getStation() << "\t" << d.getDay() << " " << d.getYear() << "\t" << d.getSunrise() << "\t" << d.getSunset() << "\t" << d.getRealCoordinates().latitude << "\t" << d.getRealCoordinates().longitude << "\t" << d.getSGPSCoordinates().latitude << "\t" << d.getSGPSCoordinates().longitude << "\t" << d.getErrorDegree().latitude << "\t" << d.getErrorDegree().longitude << "\t" << d.getErrorHaversine() << "\t" << d.getErrorKm().latitude << "\t" << d.getErrorKm().longitude << "\t" << d.getErrorPercent().latitude << "\t" << d.getErrorPercent().longitude << "\t" << d.getSunrise() << "\t" << d.getSunset() << endl;
		all.close();
	
}	
