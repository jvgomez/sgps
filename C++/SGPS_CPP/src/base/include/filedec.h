/*
 * file.h
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

#ifndef FILEDEC_H_
#define FILEDEC_H_


#include <vector>
#include <boost/algorithm/string.hpp>
#include <boost/filesystem.hpp>
#include "file.h"
#include "day.h"

class FileDec: public File {
public:
    FileDec();
    FileDec(const boost::filesystem::path, float sr = 10, float ss = 10);
    virtual ~FileDec();

    void info () const;

    Day read (bool saveData = false);
};


#endif /* FILEDEC_H_ */
