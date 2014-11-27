/*
 * diranalyzer.cpp
 * Class to obtain the files with the sunlight data.
 * Part of the SGPS Project. http://www.sgpsproject.org
 * Copyright (C) 2012 Javier V. Gómez, Isaac Rivero
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
#include <pwd.h>
#include <boost/algorithm/string.hpp>
#include "../include/diranalyzer.h"
#include "../include/logger.h"
#include "../include/console.h"
#include "../include/huefile.h"

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
	//getNOAAFiles(); //Extract those files which are NOAA-compliant.
	
	// LLamar a opciones y coger el vector de string;
	getValidFiles();
}

void DirAnalyzer::getValidFiles() { 
	
	Options * opt =  Options::Instance();
	
	
	for (vector<File>::iterator it (files.begin()); it!=files.end(); ++it) {
		unsigned int size = file_size(it->getPath());
		
		////NOAAFile
		if (( (size >= 339885) && (size <= 339892) ) || ( (size >= 113325) && (size <= 113332) )|| it->getSkipFile()==0) {
			File * filePtr = new NOAAFile(it->getPath());
			validFiles.push_back(filePtr);
		}
		////NO NOAA File
		else{
				fstream stored;
				char s[30];
				
				string name;
				
				name = it->getName();
				
				stored.open(it->getPath().c_str(), fstream::in);				
				
				stored.getline(s, 30);			
				
				
				if (strcmp (s, "genericfile") == 0){
					
					File * filePtr = new File(it->getPath());
					validFiles.push_back(filePtr);
				}
				
				else if (strncmp (name.c_str(), "imgftxx", 5) == 0){   //////MIRAR!!!!!!
					
					File * filePtr = new HUEFile(it->getPath());
					validFiles.push_back(filePtr);
				}
				
				else {
					
					if (opt->getLoggerOp() == true){
						Logger::invalidFiles(it->getName(), it->getPath(), 2);
					}
				
	
					if (opt->getConsoleOp() == true || opt->getFileReadedOp() == true){
						Console::invalidFiles(it->getName(), it->getPath(), 2);
					}
				}
		} 
	}
	
}
		


//void DirAnalyzer::getNOAAFiles() {
	//int coun = 0;
	//Options * opt =  Options::Instance();
	
	//for (vector<File>::iterator it (files.begin()); it!=files.end(); ++it) {
			//unsigned int size = file_size(it->getPath());

			////File with 1 measure every 3 minutes or every 1 minutes without errors.
			//if (( (size >= 339885) && (size <= 339892) ) || ( (size >= 113325) && (size <= 113332) )) {
				//File * filePtr = new NOAAFile(it->getPath());
				//validFiles.push_back(filePtr);
				////Console::validFiles(filePtr->getName(), filePtr->getPath());
			//}
			//else {
				

				//if (opt->getLoggerOp() == true){
					//Logger::invalidFiles(it->getName(), it->getPath(), 2);
				//}
				
	
				//if (opt->getConsoleOp() == true){
					//Console::invalidFiles(it->getName(), it->getPath(), 2);
				//}
				////// TODO: include this part with Logger.
				////*files_discarded++;
				////string name=it->getPath();
				////char * name_cstr = new char [name.size()+1];
				////strcpy (name_cstr, name.c_str());
				////fstream outputFile("Results/skipped.txt", fstream::out | fstream::app);
				////outputFile<<name_cstr<<"\t\tReason: 2"<<endl;
				////outputFile.close();
				////delete[] name_cstr;*/
			//}
			
	//}
//}

vector<Day> DirAnalyzer::readFiles () {
	vector<Day> days;

	
	for (vector<File*>::iterator it (validFiles.begin()); it!=validFiles.end(); ++it) {
				
					Day d = (*it)->read();
				
					if ((*it)->getSkipFile()==0){
				
						d.setFile(*it);
						days.push_back(d);
					}			
	}
	
	return days;
}

void DirAnalyzer::info () {
	
	Options * opt =  Options::Instance();
	
	if (opt->getConsoleOp() == true){
		Console::totalFiles(files.size(), validFiles.size());
	}
	
	
	//cout << " There are " << files.size() <<" files." << endl;
	//cout << validFiles.size() <<" are valid files." << endl;

	//for (vector<File*>::iterator it (validFiles.begin()); it!=validFiles.end(); ++it)
	//	(*it)->info(); // it is the pointer to File*, *it is the object File*, (*it) is the pointer to the object of File*
					   // *it ->function() means  *( (*it).function() )
					   //(*it)->function() means (*(*it)).function()


}


string DirAnalyzer::createDir(const string namedir){

    Options * opt = Options::Instance();

    struct passwd *pw = getpwuid(getuid());
    //const char *homedir = pw->pw_dir;
    //string name = homedir;

    //string path = name + "./output/";
    string path = "../output/";

    string total;
    total = path +namedir;

    ifstream r;
    r.open(path.c_str());

    if (!r)
    {
        create_directory(path.c_str());
    }

    opt-> setOutputPath(path);

    return total;
}

Day DirAnalyzer::extractDay(string path){
	
	//TODO: implement a version that given a Day d which has not
	//stored the values of Day::times_ and Day::values_, opens its corresponding
	//file and reads them.
	Day d;
	File *f;
	bool aux = 1;
	
	Options * opt = Options::Instance();

	//TODO: it the future this will be required to be generalized.
	//For this application it is supposed that this will have only one file type. So
	//we avoid to look for all the file types.
	if (opt->isFileType("generic"))
		f = new File(path);
		
	else if (opt->isFileType("noaa"))	
		f = new NOAAFile(path);
		
	else if (opt->isFileType("huefile"))	
		f = new HUEFile(path);
		
	else {
		vector<string> s = opt->getFileTypes();
		stringstream ss;
		ss << "File type not found: " << s.at(0) << ". Check the spelling and the available file types.";
		Console::error(ss.str());
		aux = 0;
	}
	
	if(aux == 1) {
		d = f->read(true);
	}
	
	return d;
}

