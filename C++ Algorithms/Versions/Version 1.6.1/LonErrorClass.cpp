#include <math.h>
#include <iostream>


#define RAD2DEG 180.f/M_PI
#define DEG2RAD M_PI/180.f

double g(int y, int m, int d)
{
	m = (m + 9) % 12;
	y = y - m/10;
	return 365*y + y/4 - y/100 + y/400 + (m*306 + 5)/10 + ( d - 1 );
}

double NumberDaysOfDate(int year, int month, int day)
{
	using namespace std; 
	double dateOnDays;
	dateOnDays = g(year, month, day) - 693899; // 693899 is the number of days - 2, where date is 01/01/1900											
	return dateOnDays;
}
//I dont need use this procedure. The error in longitude can be calculated muliply SR and SS by 24.
/*double HourSinceNumber (double decimal, int type)
{
	
	
	double param, fractPart, intPart;
	double auxFractPart, auxIntPart;
	
	//cout << endl << "hourSinceNumber, init param; decimal: " << decimal << ". type: " << type;
	
	param = decimal;
	param = param * 24;
	fractPart = modf(param, &intPart);
	switch(type){
		case 1: fractPart = intPart;
		   break;
		case 2: fractPart = fractPart * 60;
		   break;
		case 3: fractPart = fractPart * 60;
			auxFractPart	= modf(fractPart, &intPart);
			//if ( intPart == 0) 
				//intPart = 0.00000000001;
			auxFractPart = fmod(fractPart , intPart);
			fractPart = auxFractPart * 60;	 
		   break;
		default: fractPart = decimal;
	};
	if (isnan(fractPart)) fractPart = 0.0;
	//cout << endl << "hourSinceNumber, return: " << fractPart;
	return fractPart;
}*/

double getErrorLonValue(int year, int month, int day, double lon, double lat,  int timeZone)
{ 
		double julianDay;
		double days;
		double timePLM = 0.5;
		double julianCentury;
		double geomMeanLongSun;
		double geomMeanAnomSun;
		double eccentEarthOrbit;
		double sunEqOfCtr;
		double sunTrueLong;
		double sunTrueAnom;
		double sunRadVector;
		double sunAppLong;
		double meanObliqEcliptic;
		double obliqCorr;
		double sunRtAscen;
		double sunDeclin;
		double varY;
		double eqOfTime;
		double haSunrise;
		double solarNoon;
		double sunrise;
		double sunset;
		double sr;
		double ss;
		double midday;
		double longitude;
		double errorLongitude;
		lat = -60;
		lon = 50;
		days 			 	= NumberDaysOfDate(year, month, day);
		julianDay 		 	= days + 2415018.5 + timePLM - (timeZone / 24);
		julianCentury 	 	= (julianDay - 2451545.0) / 36525.0;
		double aux	 	= 280.46646 + (julianCentury *(36000.76983 + (julianCentury * 0.0003032)));		
		geomMeanLongSun = fmod(aux,360);
		geomMeanLongSun = 360 + geomMeanLongSun;
		geomMeanAnomSun  	= 357.52911 + (julianCentury * (35999.05029 - (0.0001537 * julianCentury)));
		eccentEarthOrbit 	= 0.016708634 - (julianCentury * (0.000042037 + (0.0001537 * julianCentury)));
		sunEqOfCtr 		 	= sin( geomMeanAnomSun * DEG2RAD) * (1.914602 - (julianCentury * (0.004817 + 
							(0.000014 * julianCentury)))) + 
							sin( 2 * geomMeanAnomSun * DEG2RAD) * (0.019993 -  (0.000101 * julianCentury)) + 
							(sin (3 * geomMeanAnomSun) * 0.000289);
		sunTrueLong 		= geomMeanLongSun + sunEqOfCtr;
		sunTrueAnom		 	= geomMeanAnomSun + sunEqOfCtr;
		sunRadVector	 	= ( 1.000001018 * ( 1 - pow(eccentEarthOrbit,2))) / 
							(1 + (eccentEarthOrbit * (cos(DEG2RAD* sunTrueAnom))));
		sunAppLong		 	= sunTrueLong - 0.00569 - (0.00478 * (sin( DEG2RAD * (125.04 - (1934.136 * julianCentury)))));
		meanObliqEcliptic	= 23 + ((26 +  ((21.448 - (julianCentury * (46.815 + julianCentury * ((0.00059 - (julianCentury * 0.001813)))))) / 60)) / 60);
		obliqCorr 			= meanObliqEcliptic + (0.00256 * cos(DEG2RAD * (125.04 - (1934.136 * julianCentury))));
		sunRtAscen			= RAD2DEG * atan2(cos(DEG2RAD * sunAppLong),cos(DEG2RAD * meanObliqEcliptic) * (sin(DEG2RAD * sunAppLong)));
		sunDeclin 			= RAD2DEG * ( asin( sin(DEG2RAD * obliqCorr) * sin (DEG2RAD * sunAppLong)));
		varY				= tan( DEG2RAD * (obliqCorr/2)) * (tan(DEG2RAD * (obliqCorr / 2)));
		eqOfTime			= 4 * RAD2DEG *( (varY * sin(2 * DEG2RAD * geomMeanLongSun)) - 
							  (2 * eccentEarthOrbit * sin(DEG2RAD * geomMeanAnomSun)) + 
							  (4 * eccentEarthOrbit * varY * sin(DEG2RAD * geomMeanAnomSun) * cos(2 * (DEG2RAD * geomMeanLongSun))) - 
							  (0.5 * pow(varY,2) * sin(4 * (DEG2RAD * geomMeanLongSun))) - 
							  (1.25 * pow(eccentEarthOrbit,2) * sin(2 * (DEG2RAD * geomMeanAnomSun))));
		
		haSunrise 	= RAD2DEG * acos( cos(DEG2RAD * 90.833) / cos (DEG2RAD * lat) * cos(DEG2RAD * sunDeclin) - tan (DEG2RAD * lat) * tan(DEG2RAD * sunDeclin));
		solarNoon	= (720 -  (4 * lon) - eqOfTime + (timeZone * 60))/1440;
		sunrise		= solarNoon - haSunrise * 4 / 1440;
		sunset		= solarNoon + haSunrise * 4 / 1440;
		sr			= sunrise * 24;
		ss			= sunset * 24;
		if (sr < 0) sr += 24;		
		if (ss  < 0) ss  += 24;
		midday		= (sr + ss) / 2;
		if (sunrise < 0) midday -= 12;
		longitude 	= 180 / 12 * (12 - midday);
		errorLongitude = lon - longitude;
		return errorLongitude;
}
