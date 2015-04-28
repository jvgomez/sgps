/*
 * file.cpp
 * Class to store file data (size, path...)
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
#include "../include/file.h"
#include "../include/options.h"
#include "../include/logger.h"
#include "../include/console.h"

using namespace std;
using namespace boost::filesystem;

File::File()
{
    setSkipFile(0);
}

File::File(const path p, float sr, float ss)
{
    name  = p.filename().string();
    ppath = p.string();
    size  = file_size(p);
    sslimit = ss;
    srlimit = sr;
}

File::~File()
{
}

void File::info () const {
    cout << "Basis file: " << name << endl;
}


Day File::read (bool saveData) {

    Options * opt =  Options::Instance();

    Day d;
    fstream stored;

    d.setStation ("generic station");


    stored.open(ppath.c_str(), fstream::in);


    if (stored.good()) {
        //TODO: Improve these lines with "getline" command. Much easier to understand.
        string s;
        stored >> s;

        float latitude, longitude;
        stored >> longitude >> latitude;
        Coordinates c;
        c.latitude = latitude;
        c.longitude = longitude;
        d.setRealCoordinates(c);


        //The file pointer is moved to the day position.
        int day, month, year;
        stored>>day>>month>>year;
        // http://www.epochconverter.com/epoch/daynumbers.php
        day = day + ((month < 3) ?
        (int)((306 * month - 301) / 10) :
        (int)((306 * month - 913) / 10) + ((year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)) ? 60 : 59));
        d.setDay(day);
        d.setYear(year);

        float hour, min, seconds, auxvalues;
        string hour1, hour2;
        while(!stored.eof())
        {
            string auxhour;
            stored >> auxhour;

            hour1=auxhour[0];//Do a string with the numbers that I want
            hour2=auxhour[1];
            hour1=hour1 + hour2;

            hour=atof(hour1.c_str());//Convert de string t int

            hour1=auxhour[3];
            hour2=auxhour[4];
            hour1=hour1 + hour2;

            min=atof(hour1.c_str());

            hour1=auxhour[6];
            hour2=auxhour[7];
            hour1=hour1 + hour2;

            seconds=atof(hour1.c_str());

            hour = hour + min/60;
            hour = hour + seconds/3600;//pass seconds to hours

            times.push_back(hour);

            stored >> auxvalues;
            values.push_back(auxvalues);

        }


        File::setSkipFile(0);
        d.setTransitions(0);
        float sunrise = findSunrise(times, values);
        float sunset = findSunset(times, values);
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


float File::findSunrise(const vector<float> & times, const vector<float> & values) {
    for(int i=1;i<values.size()-2;i++) {

        if(values[i]>=srlimit && values[i+1]>=srlimit && values[i+2]>=srlimit)
            return times[i];
    }

}

float File::findSunset(const vector<float> & times, const vector<float> & values) {
    for(int i=values.size();i!=0;i--) {

        if(values[i]>=sslimit && values[i-1]>=sslimit && values[i-2]>=sslimit)
            return times[i];
    }
}
