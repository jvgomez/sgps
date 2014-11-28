/*
 * sgps.cpp
 * Main SGPS Class' body. This is the starting point.
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
#include <sstream>
#include <string>
#include <boost/progress.hpp>
#include "../include/sgps.h"
#include "../include/options.h"
#include "../include/console.h"
#include "../include/astroalg.h"



using namespace std;
using namespace boost::filesystem;

SGPS::SGPS() {

}

SGPS::~SGPS() {
}

void SGPS::readFolder(const path folder_path) {
    dirAnalyzer.extractValidFiles(folder_path);
    dirAnalyzer.info(); // TODO: hacerlo mediante console
}

void SGPS::readFiles () {

    days = dirAnalyzer.readFiles();
}


void SGPS::computeCoordinates(){


    Options * opt = Options::Instance();

    Plotter plotter_(opt->getWorldOp());//si pongo bool en el contructor

    for (vector<Day>::iterator it (days.begin()); it != days.end(); ++it) {
        Coordinates c = CelestialModel::inverseCelestialModel(*it);
        it->setSGPSCoordinates(c);
        if (opt->getConsoleOp() == true){
            Console::printCoordinates(c);
        }

        it->getError();

        if (opt->getLoggerOp() == true){
            //Logger::printCoordinates(c);
            Logger::all(*it);
        }

        if (opt->getPlotterOp() == true){
            plotter_.plotCoordinates (c, it->getStation(), days.size());
        }


    }

    if (opt->getPlotterOp() == true){
            plotter_.lastPlot();
            Plotter::wait_for_key();
        }



}

Coordinates SGPS::getCoordinates(Day &) {

}

int SGPS::getCoordinates (std::vector<Coordinates> &realC){

    for (int i=0; i != days.size(); ++i){

        realC.push_back(days[i].getRealCoordinates());
    }

    return realC.size();
}

int SGPS::getSGPSCoordinates (std::vector<Coordinates> &sgpsC){

    for (int i=0; i != days.size(); ++i){

        sgpsC.push_back(days[i].getSGPSCoordinates());
    }

    return sgpsC.size();
}




void SGPS::parseArguments (int argc, char* argv[]){

    Options * opt = Options::Instance();
    string v("");
    vector<float> vals;

    opt -> setWorldPath (argv[1]);//PARA GUARDAR DONDE ESTA EL ARCHIVO DE WORLD.DAT

    if (argc > 2){

        int index = Console::parseArguments(argc, argv, "-l", v);

        if (index > 1) { // index > 1 means that this option has been found in the arguments.
            opt-> setLoggerOn();
            Logger::startFiles();
        }

        index = Console::parseArguments(argc, argv, "-s", vals);
        if (index > 1){
            if (vals.size() != 2)
                Console::error("-s option (set light thresholds) not correctly set. It needs two values.");
            else
                opt->setLimits(vals);
        }

        index = Console::parseArguments(argc, argv, "-c", v);
        if (index > 1)
            opt-> setConsoleOn();

        index = Console::parseArguments(argc, argv, "-p", v);
        if (index > 1)
            opt-> setPlotterOn();

        index = Console::parseArguments(argc, argv, "-w", v);
        if (index > 1)
            opt-> setWorldOn();

        index = Console::parseArguments(argc, argv, "-r", v);
        if (index > 1)
            opt-> setFileReadedOn();

        index = Console::parseArguments(argc, argv, "-g", v);//POR DEFECTO HACE MUCHAS, A NO SER QUE ESPECIFIQUE QUE HAGA 1
        if (index > 1)
            opt->setOneGraphdOn();

        vector<int> vals;
        index = Console::parseArguments(argc, argv, "-h", vals);
        if (index > 1)
            if (vals.size() == 0){// Option but no values.
                Console::error("Parameters for option -h (column number) not introduced.");
                if (argc == 3){ /////////////////////////////TENIENDO EN CUENTA QUE SOLO PONGO UN ARGUMENTO, LA H
                    opt-> setLoggerOn();/////////////////////ENTONCES POR DEFECTO HARÁ TODO; LOGGER PLOTTER CONSOLE
                    Logger::startFiles();
                    opt-> setConsoleOn();
                    opt-> setPlotterOn();
                    opt-> setWorldOn();
                }
            }
            else
                for (vector<int>::iterator it (vals.begin()); it != vals.end(); ++it)
                    opt->setColumnNumber(*it);

                if (argc == 4){ /////////////////////////////TENIENDO EN CUENTA QUE SOLO PONGO UN ARGUMENTO, LA H
                    opt-> setLoggerOn();/////////////////////ENTONCES POR DEFECTO HARÁ TODO; LOGGER PLOTTER CONSOLE
                    Logger::startFiles();
                    opt-> setConsoleOn();
                    opt-> setPlotterOn();
                    opt-> setWorldOn();
                }

        vector<string> filetypes;
        index = Console::parseArguments(argc, argv, "-f", filetypes);
        if (index > 1) {
            if (filetypes.size() == 0) // Option but no values.
                Console::error("Parameters for option -f (file types) not introduced.");
            else
                for (vector<string>::iterator it (filetypes.begin()); it != filetypes.end(); ++it)
                    opt->addFileType(*it);
        }
    }
    else {
        opt-> setLoggerOn();
        Logger::startFiles();
        opt-> setConsoleOn();
        opt-> setPlotterOn();
        opt-> setWorldOn();
    }

}













