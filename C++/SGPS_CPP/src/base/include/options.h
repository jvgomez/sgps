/*
 * options.h
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

#ifndef OPTIONS_H_
#define OPTIONS_H_


#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>


//Class designed using the Singleton design pattern.
class Options {

public:
    static Options * Instance();

    ~Options () {
        if(instance_ != NULL) delete instance_;
    }

    /*static void destroyOptions(){
          if(instance_ != NULL) delete instance_;
        }*/

    /**
     * Method to get the option of Logger.
     * @return looger_ option.
     * */
    bool getLoggerOp () const				{return logger_;}
    /**
     * Method to save the option of Logger.
     * @param looger_ option.
     * */
    void setLoggerOn ()					{logger_ = true;}
    /**
     * Method to get the option of Console.
     * @return console_ option
     * */
    bool getConsoleOp () const				{return console_;}
    /**
     * Method to save the option of Console.
     * @param console_ option.
     * */
    void setConsoleOn ()					{console_ = true;}
    /**
     * Method to get the option of Plotter.
     * @return plotter_ option.
     * */
    bool getPlotterOp () const				{return plotter_;}
    /**
     * Method to save the option of Plotter.
     * @param plotter_ option.
     * */
    void setPlotterOn ()					{plotter_ = true;}
    /**
     * Method to save the option of print only the file readed.
     * @return readed_ option.
     * */
    bool getFileReadedOp () const				{return readed_;}
    /**
     * Method to save the option of print only the file readed.
     * @param readed_ option.
     * */
    void setFileReadedOn ()					{readed_=true;}
    /**
     * Method to get the option of print the world in the plots.
     * @return world_ option.
     * */
    bool getWorldOp () const				{return world_;}
    /**
     * Method to save the option of print the world in the plots.
     * @param world_ option.
     * */
    void setWorldOn ()						{world_ = true;}
    /**
     * Method to get the option of print the world in the plots.
     * @return world_ option.
     * */
    bool getOneGraphOp () const				{return onegraph_;}
    /**
     * Method to save the option of print the world in the plots.
     * @param world_ option.
     * */
    void setOneGraphdOn ()						{onegraph_ = true;}

    void setLimits(const std::vector<float> limits) {
        limits_ = limits;
    }

    /**
     * Add a new file type to be taken into account. This is the way to
     * specify the program which kind of files has to take into account.
     * @param s the name given for the files. So far, there is "noaa" and "generic".
     * */
    void addFileType(const std::string &s);

    /**
     * Returns all the file types taken into account in a vector of strings.
     * @return a vector of strings, which each element is one file type.
     * */
    std::vector<std::string> getFileTypes() const					{return fileTypes_;}


    /**
     * Says if the demanded file type is already included and being taken into account.
     * @param s the string representing a file type.
     *
     * @return bool true if the file type is included. False otherwhise.
     * */
    bool isFileType (const std::string &s);

    /**
     * Method to get files path
     * @return files path.
     * @see setPath()
     * */
    std::string getPath() 										{return path;}
    /**
     * Method to save files path
     * @param files path.
     * @see getPath()
     * */
    void setPath(std::string p) 									{path=p;}

    /**
     * Method to get world file path
     * @return world file path.
     * @see setWorldPath()
     * */
    std::string getWorldPath() 											{return worldpath;}
    /**
     * Method to save world file path
     * @param world file path.
     * @see getWorldPath()
     * */
    void setWorldPath(std::string p) 									{worldpath=p;}

    /**
     * Method to get output path
     * @return output path.
     * @see setOutputPath()
     * */
    std::string getOutputPath() 											{return outputpath;}
    /**
     * Method to save output path
     * @param output path.
     * @see getOutputPath()
     * */
    void setOutputPath(std::string p) 										{outputpath=p;}

    /**
     * Method to get column number for huefiles
     * @return column number
     * @see setColumnNumber()
     * */
    int getColumnNumber() 											{return column_number;}
    /**
     * Method to save column number for huefiles
     * @param column number
     * @see getColumnNumber()
     * */
    void setColumnNumber(const int &s) 									{column_number = s;}

    std::vector<float>& getLimits()                         {return limits_;}

protected:
    Options();
    Options (const Options & ) ;
    Options & operator = (const Options & ) ;



private:
    static Options * instance_;
    bool logger_; //Logger option
    bool console_;
    bool plotter_;
    bool onegraph_;
    bool world_;
    bool readed_;
    std::string path;
    std::string worldpath;
    std::string outputpath;
    int column_number;

    std::vector<float> limits_;

    std::vector<std::string> fileTypes_;

};


#endif /* OPTIONS_H_ */
