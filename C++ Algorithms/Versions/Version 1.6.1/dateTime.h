#include <iostream> 
#include <math.h>

using namespace std;

float g(int y, int m, int d)
{
	m = (m + 9) % 12;
	y = y - m/10;
	return 365*y + y/4 - y/100 + y/400 + (m*306 + 5)/10 + ( d - 1 );
}

float NumberDaysOfDate(int year, int month, int day)
{
	using namespace std; 
	float dateOnDays;
	dateOnDays = g(year, month, day) - 693899; // 693899 is the number of days - 2, where date is 01/01/1900											
	return dateOnDays;
}

float HourSinceNumber (float decimal, int type)
{
	
	
	double param, fractPart, intPart;
	double auxFractPart, auxIntPart;

	param = decimal;
	fractPart = modf(param, &intPart);
	switch(type){
		1: fractPart = intPart;
		   break;
		2: fractPart = fractPart * 60;
		   break;
		3: fractPart = fractPart * 60;
	   	   auxFractPart	= modf(fractPart, &intPart);
		   auxFractPart = fractPart % intPart;
		   fractPart = auxFractPart * 60;	 
		   break;
		default: fractPart = decimal;
	};
	return fractPart;
}

