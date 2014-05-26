#include <iostream>
#include <vector>
#include <boost/progress.hpp>


#include <sgps/sgps.h>


using namespace std;

int main (int argc, char* argv[]) {
	
	SGPS::parseArguments(argc, argv);
	
	DirAnalyzer dir;	
	
	Day d = dir.extractDay(argv[1]);
	
	d.setSGPSCoordinates(CelestialModel::ForwardCelestialModel(d));
	
	Plotter::plotCoordinatesDay(d, argv[2]);
	
	return 0;
}
