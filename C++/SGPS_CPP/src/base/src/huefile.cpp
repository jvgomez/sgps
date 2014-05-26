/*
 * huefile.cpp
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



#include <iostream>
#include <fstream>
#include "../include/huefile.h"
#include "../include/options.h"
#include "../include/logger.h"
#include "../include/console.h"


using namespace std;
using namespace boost::filesystem;


HUEFile::HUEFile() {

}

HUEFile::HUEFile(const path p)
{
	//TODO: name  = p.filename().string(); for Boost >1.46
	name  = p.filename().string();
	ppath = p.string();
	size  = file_size(p);
	column = 4;
	sslimit = 10;
}



HUEFile::~HUEFile() {

}


void HUEFile::info () const {
	cout << "HUE file: " << name << endl;
}


Day HUEFile::read (bool saveData) {
	
	Options * opt =  Options::Instance();
	
	Day d;
	fstream stored;
	
	int col = opt->getColumnNumber();
	if (col > 4)
		column = col;     ////////////GUARDO LA COLUMNA QUE COGERE Y LUEGO USARÉ
	
	switch (column){	/////////////PONGO EL LIMITE PARA SUNRISE Y SUNSET
		case 4: sslimit = 9;
				break;
		case 5: sslimit = 0.9;
				break;
		case 6: sslimit = 0.3;
				break;
		case 7: sslimit = 0.1; ////NO TIENE UN LIMITE POR ABAJO
				break;		
		case 8: sslimit = 0.1;
				break;	
		case 9: sslimit = 10;
				break;	
		case 10: sslimit = 20;
				break;
		case 11: sslimit = 30;
				break;
		case 12: sslimit = 15;
				break;
		case 13: sslimit = 0.1;
				break;
		case 14: sslimit = 0.1;
				break;	
	}	
	
	stored.open(ppath.c_str(), fstream::in);
	

	if (stored.good()) {
		//TODO: Improve these lines with "getline" command. Much easier to understand.
		
		float latitude, longitude;
		stored >> longitude >> latitude;
		Coordinates c;
		c.latitude = latitude;
		c.longitude = longitude;
		d.setRealCoordinates(c);
	
	
		string s;
		stored >> s;
		d.setStation (s);

		//The file pointer is moved to the day position.
		int day, moth;
		stored>>day>>moth;
		if (moth==3){//Si el mes es 3(marzo), cuento los 28 dias de febrero, y los 31 de enero
			day = day +28+31;
		}
		else if (moth<=7 && moth%2==0 && moth !=2){
			day = day + (moth/2)*31 + (moth/2-1)*30 + 28;//Si el mes es par antes de julio, cuento la mitad de meses 31, febrero con 28, y los demas con 30
		}
		else if (moth>7 && moth%2==0){
			day = day + (moth/2+1)*31 + (moth/2-2)*30 + 28;//Si el mes es par despues de julio, cuento la mitad mas 1 de meses 31(por agosto), febrero con 28, y los demas con 30
		}
		else if (moth<=7 && moth%2!=0 && moth !=1 && moth !=3){
			day = day + (moth/2-1)*30 + (moth/2+1)*31 + 28;
		}
		else if (moth>7 && moth%2!=0){
			day = day + (moth/2-1)*30 + (moth/2+1)*31 + 28;
		}
		else if (moth == 1){
			day = day;
		}
		else if (moth == 2){
			day = day + 31;
		}	
		d.setDay(day);

		
		//The file pointer is moved to the year position.
		int year;
		stored >> year;
		d.setYear(year);
		
		
		stored >> elevation;
		
		float hour, min, seconds, auxvalues, transitions=0;
		float a;
		
		while(!stored.eof())
		{

			stored >> hour >> min >> seconds;
			
			hour = hour + min/60;
			hour = hour + seconds/3600;//pass seconds to hours
			
			times.push_back(hour);
	
			 
			for (int i=4; i<column; i++){
				stored >> a;
			}
			
			stored >> auxvalues;
			values.push_back(auxvalues);
			
			
			for(int z=column; z<14; z++){
				stored >> a;
			}
			
		}
		
	
		File::setSkipFile(0);
		d.setTransitions(0);	
		float sunrise = File::findSunrise(times, values);
		float sunset = File::findSunset(times, values);
		d.setSunrise(sunrise);
		d.setSunset(sunset);
		
		// Not saved by default (consumes time and a lot of memory).
		if (saveData) {
			d.setTimes (times);
			d.setValues (values);
		}
		
		
		if (opt->getConsoleOp() == true || opt->getFileReadedOp() == true){
			Console::validFiles (name, ppath, File::getSkipFile());
		}
		if (opt->getConsoleOp() == true){
			Console::placeInfo(d, values.size());
		}
		if (opt->getLoggerOp() == true){
			Logger::placeInfo(d, values.size());
			Logger::validFiles(name, ppath, File::getSkipFile(), d);//save in a file the number of valid files
		}
		
		return d;

	}	
	
}



