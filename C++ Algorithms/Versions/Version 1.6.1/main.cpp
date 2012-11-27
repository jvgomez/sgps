#include <iostream>
#include <fstream>
#include <cmath>
#include <string>

#include <cstring>
#include <vector>
#include <ctime>
#include "diranalyzer.h"
#include "LonErrorClass.cpp"

//Namespaces are included in the DirAnalyzer class.

//Reason for skipping: 1 -> First file of each station with fractionated day.
//					   2 -> File with size not valid.
//					   3 -> More than 2 transitions in one day.
//					   4 -> Some data is corrupt.
//					   5 -> Error when finding out SR or SS.
//					   6 -> There are many measurements with value 0 followed
//					   7 -> Equinox day


#define RAD2DEG 180.f/M_PI
#define DEG2RAD M_PI/180.f

typedef struct 
{
	vector <float> times;
	vector <float> values;
	float 	real_latitude;
	float 	real_longitude;
	int 	day;
	int 	year;
	char 	station_name[30];
	//int gmt; //Not necessary, the files have the data in UTC format.
}data;

bool fractionated_day=false;
int  contador = 60;

data 	readData		(char * filename, int &skip);
float  	getSR 			(data measures, float threshold, int &skip, int transitions);
float  	getSS 			(data measures, float threshold, int &skip, int transitions);
void 	getCoordinates	(float *coordinates, int d, float srTime, float ssTime, float errorLonCalculated);
int 	getTransitions	(data measures);
int 	getMonth		(int measureDay, int &day); //Return the day of Gregorian calendar.

int main(int argc, char* argv[])
{
	DirAnalyzer  file_search;
	vector<File> files;
	vector<File> files_to_read;
	
	int 	files_discarded = 0;
	int 	count 	= 0;
	int 	month   = 1;
	int 	day 	= 1;
	float 	max_avg = 0.0;
	float 	max_ins = 0.0;
	float 	errorLonCalculated;
	double 	time;
	clock_t s,e;
	
	s = clock();
		
	file_search.getFiles(argv[1], files);
	
	for (vector<File>::iterator it (files.begin()); it!=files.end(); ++it)
	{
		unsigned int size=file_size(it->getPath()); 
		
		//File with 1 measure every 3 minutes o every 1 minutes without mistakes.
		if (((size>=339885)&&(size<=339892)) || ((size>=113325)&&(size<=113332)))
			files_to_read.push_back(*it);
		else
		{
			files_discarded++;
			string name=it->getPath();
			char * name_cstr = new char [name.size()+1];
			strcpy (name_cstr, name.c_str());
			fstream outputFile("Results/skipped.txt", fstream::out | fstream::app);
			outputFile<<name_cstr<<"\t\tReason: 2"<<endl;
			outputFile.close();	
			delete[] name_cstr;
		}
		
	}
	
	cout<<"The program will read "<<files_to_read.size()<<" files."<<endl;
	cout<<files_discarded<<" files were discarded."<<endl;
	
	for (vector<File>::iterator it (files_to_read.begin()); it!=files_to_read.end(); ++it)
	{
		count++;
		float sr;
		float ss;
		float light_average;
		float threshold;
		float sum_all;
		
		//Opening and reading the file
		string name=it->getPath();
		char * name_cstr = new char [name.size()+1];
		strcpy (name_cstr, name.c_str());
		
		int skip_file = 0; //Variable to avoid some reading errors.
		data measures=readData(name_cstr, skip_file);
		int transitions=getTransitions(measures);
		
		if (skip_file==0)
		{
			fractionated_day=false;
				
			if ((measures.day != 81) && (measures.day != 82) && (measures.day != 265) && (measures.day != 266)){
				month = getMonth(measures.day,day);
			
				int n=1;
				
				threshold = 0.0;
				sum_all = 0.0;
				
				for(vector<float>::iterator it2 (measures.values.begin()); it2!=measures.values.end(); ++it2)
				{
					
					if(*it2>=0.0)
					{
						if (*it2>max_ins) max_ins=*it2;
						sum_all+=*it2;
						n++;
					}
				}
				light_average = sum_all/n;
				
				if (light_average>max_avg) max_avg=light_average;
			
				sr = getSR(measures, threshold, skip_file,transitions);
				ss = getSS(measures, threshold, skip_file,transitions);
				
				//if((sr==0) || (sr==0)) skip_file=5;
			

				if(ss<sr) //If the sunset occurs prior the sunrise for that day
				{
					fractionated_day=true;
					
				}
			
			}
			else  {skip_file = 7;} //Equinox day.
		} //skip_file == 0;
			
		if(skip_file == 0)
		{
			float coordinates[2];
			errorLonCalculated = getErrorLonValue(measures.year, month, day, 0, 0, 0);
			getCoordinates(coordinates, measures.day, sr, ss,errorLonCalculated);

			
			//Showing the process.
			cout<<"\r\33[1;32m"<<"READING FILES...  "<<count<<"\33[0m"<<"\33[31m"<<"\t"<<name_cstr<<"\33[0m";				
			delete[] name_cstr;
			float errorLat = measures.real_latitude  - coordinates[0];
			float errorLon = measures.real_longitude - coordinates[1];
			
			//Saving the data into a file.
			if (transitions == 2)
			{
				fstream outputFile("Results/results.txt", fstream::out | fstream::app);
				
				outputFile << threshold << "\t" << measures.station_name 	<< "\t" << measures.day 		   	<< "\t" << measures.year<< "\t" << coordinates[0] << "\t"
					<< coordinates[1] 	<< "\t" << measures.real_latitude 	<< "\t" << measures.real_longitude 	<< "\t" << errorLat 	<< "\t" << errorLon  	  << "\t" 
					<< errorLat*100/180 << "\t" << errorLon*100/360  		<< "\t" << light_average 		   	<< "\t" << sr			<< "\t" << ss 			  << endl;
					
				outputFile.close();	
				
				fstream outputFile2 ("Results/Hresults.txt", fstream::out | fstream::app);
				outputFile2 << fabs(errorLat*100/180) << "\t" << fabs(errorLon*100/360) << endl;
				outputFile2.close(); 
			}
			else
			{
				if ((ss == -1)  || (sr == -1)){
					fstream outputFile("Results/resultsMoreTransitions-1.txt", fstream::out | fstream::app);
				
					outputFile << threshold << "\t" << measures.station_name 	<< "\t" << measures.day 		   	<< "\t" << measures.year<< "\t" << coordinates[0] << "\t"
					<< coordinates[1] 	<< "\t" << measures.real_latitude 	<< "\t" << measures.real_longitude 	<< "\t" << errorLat 	<< "\t" << errorLon  	  << "\t" 
					<< errorLat*100/180 << "\t" << errorLon*100/360  		<< "\t" << light_average 		   	<< "\t" << sr			<< "\t" << ss 			  << endl;
					outputFile.close();	
				}
				else{
						
					fstream outputFile("Results/resultsMoreTransitions.txt", fstream::out | fstream::app);
					
					outputFile << threshold << "\t" << measures.station_name 	<< "\t" << measures.day 		   	<< "\t" << measures.year<< "\t" << coordinates[0] << "\t"
						<< coordinates[1] 	<< "\t" << measures.real_latitude 	<< "\t" << measures.real_longitude 	<< "\t" << errorLat 	<< "\t" << errorLon  	  << "\t" 
						<< errorLat*100/180 << "\t" << errorLon*100/360  		<< "\t" << light_average 		   	<< "\t" << sr			<< "\t" << ss 			  << endl;
						
					//outputFile<<threshold<<"\t"<<light_average<<"\t"<<measures.station_name<<"\t"<<measures.day<<"\t"<<measures.year<<"\t"<<sr<<"\t"<<ss<<"\t"<<coordinates[0]<<"\t"<<coordinates[1]<<"\t"<<measures.real_latitude<<"\t"<<measures.real_longitude<<endl;
					outputFile.close();	
					
					fstream outputFile2("Results/HresultsMoreTransitions.txt", fstream::out | fstream::app);
					outputFile2 << fabs(errorLat*100/180) << "\t" << fabs(errorLon*100/360) << endl;
					outputFile2.close(); 	
				}
			}
		}
		if(skip_file > 0) //File skipped
		{
			fstream outputFile("Results/skipped.txt", fstream::out | fstream::app);
			outputFile<<name_cstr<<"\t\tReason: "<<skip_file<<endl;
			outputFile.close();	
			delete[] name_cstr;
		}	
		
	}

	e=clock();
	time=(double)(e - s) / CLOCKS_PER_SEC;
	cout <<endl<<"Time elapsed (reading and calculating): "<<time<<endl;	
	cout <<"Maximum light intensity and maximum average: "<<max_ins<<"\t"<<max_avg<<endl;	
	
	return 0;
}


data readData (char * filename, int &skip)
{
	data measures;
	float auxtime;
	float auxvalue;
	fstream stored;
	
	stored.open(filename, fstream::in);
	
	if (!stored.good())
		cout<<"File not found: "<<filename<<endl;
	else
	{
		//This value says if the measure is OK.
		int error_flag = 0;
		
		//The file pointer is moved to the coordinates position.
		stored.getline(measures.station_name,30);
		stored>>measures.real_latitude>>measures.real_longitude;
		
		//The file pointer is moved to the year position.
		stored.seekp(18, ios::cur);
		stored>>measures.year;
		
		//The file pointer is moved to the day position.
		stored>>measures.day;
		
		//Returning to the beginning of the line to start gathering data.
		stored.seekp(-9, ios::cur);
		
		while(!stored.eof())
		{
			//Reading the time of the measure.
			stored.seekp(23, ios::cur);
			stored>>auxtime;
			measures.times.push_back(auxtime);
			
			//Reading the value of the measure.
			stored.seekp(8, ios::cur);
			stored>>auxvalue;
			stored>>error_flag;
			//cout<<error_flag;
			if(error_flag==1) {
				skip = 4;
			}
			
			measures.values.push_back(auxvalue);
			
			//Moving the pointer to the end of the line.
			stored.seekp(190, ios::cur);	
		}
		
		stored.close();
	}

	//Due the way of reading the data, one more line is read. It is erased here.	
	measures.times.pop_back();
	measures.values.pop_back();
	
	return measures;
}


float getSR(data measures, float threshold, int &skip, int transitions)
{
	
	for(int i=1;i<measures.values.size()-2;i++)
	{
		if ((measures.values[i+1]>=threshold) && (measures.values[i]>=threshold) && (measures.values[i-1]<threshold))
		{
			if (transitions = 2){ 
				if (measures.values[i] == threshold) return measures.times[i];
				return (measures.times[i]+measures.times[i-1])/2.0f;		
			}
			
			int  transition1 = i; 
			int  transition2 = i;
			bool bestSR 	 = false;
			
			if (transitions > 2) {

				int aux = measures.values.size() - 2;
				
				int positiveMeasure = 0;
				
				for ( int j = i + 1; j < aux; j++) {
										
					if ( (measures.values[j + 1] < threshold) && (measures.values[j] >= threshold) ){
						transition2 = transition1; 
						transition1 = j;
					}
					if ( (measures.values[j] <= threshold) && (measures.values[j+1] > threshold) ){
						transition2 = transition1; 
						transition1 = j;
					}
					
					if (measures.values[j] > threshold) positiveMeasure += 1;
					
					if (measures.values[j] < threshold) {
						positiveMeasure = 0;
					}
					
					if (positiveMeasure > 20) { //if there are too many positive measures, for is finished. (Si hay muchas medidas positivas, sale del for)
						bestSR = true;
						j = aux;
					}
					
					if ( (j == 1) && (positiveMeasure > 5) ) bestSR = true;
				}
			}
			if  (bestSR) return (( measures.times[transition2] + measures.times[transition1]) / 2.0f); 	
			else return -1; //If dont find SR.
		}		
	}		
	return 0; //If error occurs.	
}


float getSS(data measures, float threshold, int &skip, int transitions)
{
	for(int i=measures.values.size()-2;i>0;i--)
	{

		if ((measures.values[i+1]<threshold) && (measures.values[i]>=threshold) && (measures.values[i-1]>threshold))
		{
			if (transitions == 2) {
				if (measures.values[i] == threshold) return measures.times[i];
				return (measures.times[i-1] + measures.times[i])/2.0f;		
			}
			bool bestSR 	 = false;
			int  transition1 = i; 
			int  transition2 = i;
			
			if (transitions > 2) {
				int positiveMeasure = 1;
				for (	int j = i; j > 0; j--){
					
					if ( (measures.values[j - 1] < threshold) && (measures.values[j] >= threshold) ){
						transition2 = transition1; 
						transition1 = j;
					}
					if ( (measures.values[j] <= threshold) && (measures.values[j - 1] > threshold) ){
						transition2 = transition1; 
						transition1 = j;
					}
					if (measures.values[j] > threshold) positiveMeasure += 1;
					
					if (measures.values[j] < threshold) {
						positiveMeasure = 0;
					}
					
					if (positiveMeasure > 20) { //if there are too many positive measures, for is finished. (Si hay muchas medidas positivas, sale del for)
						bestSR = true;
						j = 0;
					}
					if ( (j == 0) && (positiveMeasure > 5) ) bestSR = true;
				}
			}
			if (bestSR)return (( measures.times[transition2] + measures.times[transition1]) / 2.0f); 		
			else return -1; //If dont find SR.

		}
	}
	return 0; //If error occurs.

}


void getCoordinates(float *coordinates, int d, float srTime, float ssTime, float errorLonCalculated)
{
	float gamma = 2.f*M_PI/365.f*(d); //This is beta in the paper.
	float mdTime = (srTime+ssTime)/2.f;
	if (fractionated_day) mdTime+=12.0f; //Theorem application.
	if (mdTime >= 24) mdTime = fmod(mdTime, 24);
	
	//EqT update
	float EqT = 229.18*(0.000075 + 0.001868*cos(gamma) - 0.032077*sin(gamma) - 0.014615*cos(2*gamma) - 0.040849*sin(2*gamma));
	mdTime += EqT*24.0f/1440.0f; //Converting into hours.
	ssTime += EqT*24.0f/1440.0f; //Converting into hours.
	
	coordinates[1] = 180.f/12.f*(12-mdTime);
	//float longwError = 180.f/12.f*(12-mdTime);
	//float longError = errorLonCalculated;
	//coordinates[1] = longwError+longError;

	float delta = 0.006918f-0.399912f*cos(gamma)+0.070257f*sin(gamma)-0.006758f*cos(gamma*2)+0.000907f*sin(gamma*2)-0.002697f*cos(gamma*3)+0.00148f*sin(gamma*3);
	float tsunset = M_PI/12.f*fabs(ssTime-mdTime);
	float min_error = 10000;
	
	for (float latitude = -90; latitude <= 90; latitude += 0.1) //Numerically solving the long latitude formula.
	{
		float error_now = abs(((sin(-0.83*DEG2RAD)-sin(latitude*DEG2RAD)*sin(delta))/(cos(latitude*DEG2RAD)*cos(delta))) - cos(tsunset));
		if (error_now < min_error)
		{
			min_error = error_now;
			coordinates[0] = latitude;
		}
		
	}
}

int getTransitions(data measures)
{
	int transitions=0;
	//If the sign of this number and the previous are different, a transition has occurred.
	for(unsigned int i=1;i<measures.values.size();i++)
	{
		float sign=copysignf(1.0,measures.values[i]);
		float sign_prev=copysignf(1.0,measures.values[i-1]);
		if (sign!=sign_prev)
			transitions++;	
	}
	
	return transitions;
}

int getMonth(int measureDay, int &day) 
{
	if (measureDay <= 31) {
		day = measureDay;
		return 1;	
	}
	if ((measureDay >= 32)  &&	(measureDay <= 59))  
	{
		day = measureDay - 31;
		return 2;
	}
	if ((measureDay >= 60)  &&	(measureDay <= 90))  
	{
		day = measureDay - 59;
		return 3;
	}
	if ((measureDay >= 91)  &&	(measureDay <= 120)) 
	{
		day = measureDay - 90;
		return 4;
	}
	if ((measureDay >= 121) &&	(measureDay <= 151)) 
	{
		day = measureDay - 120;
		return 5;
	}
	if ((measureDay >= 152) &&	(measureDay <= 181)) 
	{
		day = measureDay - 151;
		return 6;
	}
	if ((measureDay >= 182) &&	(measureDay <= 212)) 
	{
		day = measureDay - 181;
		return 7;
	}
	if ((measureDay >= 213) &&	(measureDay <= 243)) 
	{
		day = measureDay - 212;
		return 8;
	}
	if ((measureDay >= 244) &&	(measureDay <= 273)) 
	{
		day = measureDay - 243;
		return 9;
	}
	if ((measureDay >= 274) &&	(measureDay <= 304)) 
	{
		day = measureDay - 273;
		return 10;
	}
	if ((measureDay >= 305) &&	(measureDay <= 334)) 
	{
		day = measureDay - 304;
		return 11;
	}
	if ((measureDay >= 335) &&	(measureDay <= 365)) 
	{
		day = measureDay - 334;
		return 12;
	}
	if (measureDay == 366){
		day = 31;
		return 12;
	}
return 0;	
}


