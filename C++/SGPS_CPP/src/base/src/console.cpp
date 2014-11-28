/*
 * console.cpp
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


#include <fstream>
#include <iostream>
#include <string>
#include <boost/algorithm/string.hpp>
#include "../include/console.h"
#include "../include/options.h"


using namespace std;

ostream& operator << (ostream& stream, Coordinates& c) {

    stream << "---------- Latitude: \33[1;36m" << c.latitude << "\33[0m" << " ---------- Longitude: \33[1;36m" << c.longitude << "\33[0m" << endl;

    return stream;
}



Console::Console() {

}



Console::~Console() {

}

void Console::printCoordinates (Coordinates c) {

        cout << c;

}

void Console::placeInfo (Day d, int measures = 0){

        cout << "\33[1;36m" << d.getStation() << " " << d.getRealCoordinates().latitude << " " << d.getRealCoordinates().longitude <<"\33[0m day info: " << d.getDay() << " " << d.getYear();

        if (measures != 0)
            cout <<" Measures taken: " << measures;

        cout << endl;
        cout <<"Day info: " << d.getDay() << " " << d.getYear() << ". Transitions: " << d.getTransitions() << ". Sunrise: " << d.getSunrise() <<  " Sunset: " << d.getSunset() << endl;

}


void Console::totalFiles(const int filesize, const int validsize){

        cout << "\33[1;1m There are " << filesize <<" files." << "\33[0m" << endl;
        cout << "\33[1;32m" << validsize <<" are valid files." << "\33[0m" << endl;

}


void Console::validFiles(const string name, const string ppath, const int skipFile){

        if(skipFile == 0){

            cout << "File reading \33[1;34m" << ppath << "\33[1;32m valid" << "\33[0m" << endl;//mirar
        }
}

void Console::invalidFiles(const string name, const string ppath, const int skipFile){

        cout << "Reading File  \33[1;34m" << ppath << " is invalid,";

        switch (skipFile){
            case 1:
                cout << "\33[1;31m error 1" << "\33[0m" << endl;
                break;
            case 2:
                cout << "\33[1;31m bad extension" << "\33[0m" << endl;
                break;
            case 4:
                cout << "\33[1;31m error flag is 1" << "\33[0m" << endl;
                break;
            case 7:
                cout << "\33[1;31m equinox" << "\33[0m" << endl;
                break;
        }
}



//IMPORTANT NOTE: findArguments functions have not been tested (just one of them).
//It is possible to have bugs here with the index numbering.

int Console::findArguments (int argc, char** argv, const char* argument_name)
{
  for (int i = 1; i < argc; ++i)
  {
    // Search for the string
    if (strcmp (argv[i], argument_name) == 0)
    {
      return (i);
    }
  }
  return (-1);
}

////////////////////////////////////////////////////////////////////////////////
int Console::parseArguments (int argc, char** argv, const char* str, std::string &val)
{
  int index = findArguments (argc, argv, str);

  if (index > 1  && index < argc)
    val = argv[index];

  return index;
}

////////////////////////////////////////////////////////////////////////////////
int Console::parseArguments (int argc, char** argv, const char* str, bool &val)
{
  int index = findArguments (argc, argv, str);

  if (index > 1 && index < argc )
    val = atoi (argv[index]) == 1;

  return index;
}

////////////////////////////////////////////////////////////////////////////////
int Console::parseArguments (int argc, char** argv, const char* str, double &val)
{
  int index = findArguments (argc, argv, str);

  if (index > 1 && index < argc )
    val = atof (argv[index]);

  return index;
}

////////////////////////////////////////////////////////////////////////////////
int Console::parseArguments (int argc, char** argv, const char* str, float &val)
{
  int index = findArguments (argc, argv, str);

  if (index > 1 && index < argc )
    val = static_cast<float> (atof (argv[index]));

  return index ;
}

////////////////////////////////////////////////////////////////////////////////
int Console::parseArguments (int argc, char** argv, const char* str, int &val)
{
  int index = findArguments (argc, argv, str);

  if (index > 1 && index < argc )
    val = atoi (argv[index]);

  return index;
}

////////////////////////////////////////////////////////////////////////////////
int Console::parseArguments (int argc, char** argv, const char* str, unsigned int &val)
{
  int index = findArguments (argc, argv, str);

  if (index > 1 && index < argc )
    val = atoi (argv[index]);

  return index;
}

////////////////////////////////////////////////////////////////////////////////
int Console::parseArguments (int argc, char** argv, const char* str, char &val)
{
  int index = findArguments (argc, argv, str);

  if (index > 1 && index < argc )
    val = argv[index][0];

  return index;
}

////////////////////////////////////////////////////////////////////////////////
int Console::parseArguments (int argc, char** argv, const char* str, vector<string> & vals)
{
  int index = findArguments (argc, argv, str);
  int i = index;
  //TODO: a default filetype should be included. Probably in the Options constructor.
    string s;
    do {
        i++;
        if (i > argc - 1) // Checking the limits
            s = '-';
        else {
            s = argv[i];
            vals.push_back(s);
        }
    } while (s[0] != '-');

  return index;
}

int Console::parseArguments (int argc, char** argv, const char* str, vector<int> & vals)
{
  int index = findArguments (argc, argv, str);
  int i = index;
  //TODO: a default filetype should be included. Probably in the Options constructor.
    string s;
    int val;
    do {
        i++;
        if (i > argc - 1) // Checking the limits
            s = '-';
        else {
            val =atoi(argv[i]);
            vals.push_back(val);
        }
    } while (s[0] != '-');

  return index;
}

int Console::parseArguments (int argc, char** argv, const char* str, vector<float> & vals)
{
  int index = findArguments (argc, argv, str);
  int i = index;
  //TODO: a default filetype should be included. Probably in the Options constructor.
    string s;
    float val;
    do {
        i++;
        if (i > argc - 1) // Checking the limits
            s = '-';
        else {
            val =atof(argv[i]);
            vals.push_back(val);
        }
    } while (s[0] != '-');

  return index;
}


void Console::warning(const std::string &val) {
    cout << "\33[1;33m" << "WARNING!: " << val << "\33[0m" << endl;

}


void Console::error(const std::string &val) {
    cout << "\33[1;31m" << "ERROR!: " << val << "\33[0m" << endl;

}


