/*
 * diranalyzer.cpp
 * Class to obtain the files with the sunlight data.
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
#include <string>
#include "../include/diranalyzer.h"

using namespace std;
using namespace boost::filesystem;

DirAnalyzer::DirAnalyzer()
{

}


DirAnalyzer::~DirAnalyzer()
{

}


void DirAnalyzer::getFiles(const path folder_path)
{
	vector<path> files_to_read = readFolder(folder_path);

	for (vector<path> ::const_iterator it (files_to_read.begin()); it != files_to_read.end(); ++it)	{
		path p = *it;
		try		{
			if (is_regular_file(p)) {       // is p a regular file?
				File new_file(p);
				/*File new_file;
				new_file.setName(p.filename());
				new_file.setPath(p.string());
				new_file.setSize(file_size(p));*/
				files.push_back(new_file);
			}

			else if (is_directory(p)) {     // is p a directory?
				getFiles(p);
			}
		}

		catch (const filesystem_error& ex) {
			cout << ex.what() << '\n';
			exit(1);
		}
	}
}


vector<path> DirAnalyzer::readFolder(const path p)
{
	vector<path> objects_in_folder;

	try	{
        typedef vector<path> vec;           // store paths
        vec v;

        copy(directory_iterator(p), directory_iterator(), back_inserter(v));
        sort(v.begin(), v.end());			// sort paths

        for (vec::const_iterator it (v.begin()); it != v.end(); ++it) {
			path fh = *it;
			objects_in_folder.push_back(fh.string());
		}

		return objects_in_folder;
	}

	catch (const filesystem_error& ex) {
		cout << ex.what() << '\n';
		exit(1);
	}
	// It is supposed this return will never be called. Just to avoid warnings in compilation.
	return objects_in_folder;
}

void DirAnalyzer::extractValidFiles(const path p) {
	getFiles(p); //Gets all the files in the path.
	getNOAAFiles(); //Extract those files which are NOAA-compliant.
}

void DirAnalyzer::getNOAAFiles() {
	int coun = 0;

	for (vector<File>::iterator it (files.begin()); it!=files.end(); ++it) {
			unsigned int size = file_size(it->getPath());

			//File with 1 measure every 3 minutes or every 1 minutes without errors.
			if (( (size >= 339885) && (size <= 339892) ) || ( (size >= 113325) && (size <= 113332) )) {
				File * filePtr = new NOAAFile(it->getPath());
				validFiles.push_back(filePtr);
			}
			else {
				// TODO: include this part with Logger.
				/*files_discarded++;
				string name=it->getPath();
				char * name_cstr = new char [name.size()+1];
				strcpy (name_cstr, name.c_str());
				fstream outputFile("Results/skipped.txt", fstream::out | fstream::app);
				outputFile<<name_cstr<<"\t\tReason: 2"<<endl;
				outputFile.close();
				delete[] name_cstr;*/
			}
	}
}

vector<Day> DirAnalyzer::readFiles () {
	vector<Day> days;
	for (vector<File*>::iterator it (validFiles.begin()); it!=validFiles.end(); ++it) {
			Day d = (*it)->read();
			d.setFile(*it);
			days.push_back(d);
			d.info();
	}
	return days;
}

void DirAnalyzer::info () {
	cout << " There are " << files.size() <<" files." << endl;
	cout << validFiles.size() <<" are valid files." << endl;

	//for (vector<File*>::iterator it (validFiles.begin()); it!=validFiles.end(); ++it)
	//	(*it)->info(); // it is the pointer to File*, *it is the object File*, (*it) is the pointer to the object of File*
					   // *it ->function() means  *( (*it).function() )
					   //(*it)->function() means (*(*it)).function()


}


