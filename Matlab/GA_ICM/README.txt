--- License ---

Part of the SGPS Project. http://www.sgpsproject.org
Copyright (C) 2012 Javier V. Gómez

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.


--- Files ---

- Data1.txt: document with the C++ results over the NOAA files. It contains: day year sunrise sunset real latitude and real longitude.

- Data2-MoreTransitions.txt: The same as Data1.txt but for those days in which it is harder to find out the sunrise and sunset times due to light transitions.

- InverseCelestialModel.m: main scripts which uses all the other files to run the genetic algorithm over the data of Data1.txt (or Data2).


Be sure that the GenAlg folder is in your Matlab/Octave path when using.




