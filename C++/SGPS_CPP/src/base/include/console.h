/*
 * console.h
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


#ifndef CONSOLE_H_
#define CONSOLE_H_


#include <string>
#include <vector>
#include "coordinates.h"
#include "day.h"



class Console {
public:
    Console();
    virtual ~Console();


    /**
     * Method to display coordinates in a file
     * @param c coordinates calculated in the program.
     * */
    static void printCoordinates(Coordinates c);

    /**
     * Method to display place information in a file
     * @param d place information
     * @param measures number of measures.
     * */
    static void placeInfo(Day d, int measures);

    /**
     * Method to display the number of total files
     * @param filesize number of total files
     * @param validfiles number of valid files.
     * */
    static void totalFiles(const int filesize, const int validsize);

    /**
     * Method to display valid files in other file
     * @param name file name
     * @param ppath file path.
     * */
    static void validFiles(const std::string name, const std::string ppath, const int skipFile);

    /**
     * Method to display valid files in other file
     * @param name file name
     * @param ppath file path
     * @param invalid the reason of invalid file.
     * */
    static void invalidFiles(const std::string name, const std::string ppath, const int skipFile);

    /**
     * Method to know the information that the user wants see
     * @param argc number of parameters that you pass to program
     * @param argv array with the parameters that you pass to program
     * */
    //static void parseArguments (int argc, char* argv[]);


    static int findArguments (int argc, char** argv, const char* argument_name);
    static int parseArguments (int argc, char** argv, const char* str, std::string &val);
    static int parseArguments (int argc, char** argv, const char* str, bool &val);
    static int parseArguments (int argc, char** argv, const char* str, int &val);
    static int parseArguments (int argc, char** argv, const char* str, float &val);
    static int parseArguments (int argc, char** argv, const char* str, double &val);
    static int parseArguments (int argc, char** argv, const char* str, unsigned int &val);
    static int parseArguments (int argc, char** argv, const char* str, char &val);
    static int parseArguments (int argc, char** argv, const char* str, std::vector<std::string> & vals);
    static int parseArguments (int argc, char** argv, const char* str, std::vector<int> & vals);
    static int parseArguments (int argc, char** argv, const char* str, std::vector<float> & vals);

    static void warning(const std::string &val);
    static void error(const std::string &val);


};

#endif /* CONSOLE_H_ */
