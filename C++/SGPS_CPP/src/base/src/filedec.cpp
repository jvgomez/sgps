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
#include "../include/filedec.h"
#include "../include/options.h"
#include "../include/logger.h"
#include "../include/console.h"

using namespace std;
using namespace boost::filesystem;


FileDec::FileDec() {
}

FileDec::FileDec(const path p, float sr, float ss) : File(p, sr, ss){
}


FileDec::~FileDec() {
}

void FileDec::info () const {
    cout << "Generic file with decimal hours: " << name << endl;
}

Day FileDec::read (bool saveData) {

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

        float hour, auxvalues;
        while(!stored.eof())
        {
            string auxhour;
            stored >> auxhour;

            hour = atof(auxhour.c_str());

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
            Console::validFiles (name, ppath, FileDec::getSkipFile());
        }
        if (opt->getConsoleOp() == true){
            Console::placeInfo(d, values.size());
        }
        if (opt->getLoggerOp() == true){
            Logger::placeInfo(d, values.size());
            Logger::validFiles(name, ppath, FileDec::getSkipFile(), d);//save in a file the number of valid files
        }

        return d;
    }
}
