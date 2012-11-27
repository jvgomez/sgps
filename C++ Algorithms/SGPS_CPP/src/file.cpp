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
#include "../include/file.h"

using namespace std;
using namespace boost::filesystem;

File::File()
{
}

File::File(const path p)
{
	//TODO: name  = p.filename().string(); for Boost >1.46
	name  = p.filename();
	ppath = p.string();
	size  = file_size(p);
}

File::~File()
{
}

void File::info () const {
	cout << "Basis file: " << name << endl;
}

Day File::read () {

}


float File::findSunrise(const vector<float> & times, const vector<float> & values) {

}

float File::findSunset(const vector<float> & times, const vector<float> & values) {

}
