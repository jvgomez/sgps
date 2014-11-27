/*
 * plotter.cpp
 * Helper class to log results data.
 * Part of the SGPS Project. http://www.sgpsproject.org
 * Copyright (C) 2013 Javier V. Gómez, Isaac Rivero
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




#include <vector>
#include <fstream>
#include <boost/algorithm/string.hpp>
#include "../include/plotter.h"
#include "../include/options.h"
#include "../include/diranalyzer.h"
#include "../include/console.h"



using namespace std;


Plotter::Plotter() {
	
	//world();

}

Plotter::Plotter(const bool &w) {
	
	if (w==true){
		world();}
		
}



Plotter::~Plotter() {

}


void Plotter::plotCoordinates (const Coordinates c, string station, int size){		
		
			
		Options * opt = Options::Instance();
		
		g1.set_xrange(-180,180);
		g1.set_yrange(-90,90);
		g1.set_xlabel("longitude");
		g1.set_ylabel("latitude");
		g1.set_title ("SGPSProject");
		g1.set_grid();
		
		
		x.push_back(c.longitude);
		y.push_back(c.latitude);
		stat.push_back(station);
		
		
		
		if (x.size()==size/60 && size > 600){/////PARA E SOLO LO HAGA SI HAY MAS DE 400 VALORES EN EL VECTOR
			g1.set_style("points").plot_xy(x, y, "");
			x.clear();
			y.clear();
			if(opt->getOneGraphOp()==false){
				g1.reset_plot();
				if(opt->getWorldOp()==true){
					world();
				}
			}
		}
		
		
}

void Plotter::lastPlot(){
	
		g1.set_style("points").plot_xy(x, y, "");
		
		

}
	
	


void Plotter::plotDay (const vector<float> & times, const vector<float> & values, const int day, const int year){

	Gnuplot g2;
	stringstream d;
	d << day << "/" << year;
	
	g2.set_title(d.str());
	g2.set_style("lines").plot_xy(times, values, "");
	Plotter::wait_for_key ();

}


void Plotter::plotCoordinatesDay(Day & d, string p){
	
	Gnuplot g3;
	
	g3.set_style ("lines").plotfile_xy(p, 1, 2, "world");
	
	vector <float> x, y, xreal, yreal;
	
	x.push_back(d.getSGPSCoordinates().longitude);
	y.push_back(d.getSGPSCoordinates().latitude);
	xreal.push_back(d.getRealCoordinates().longitude);
	yreal.push_back(d.getRealCoordinates().latitude);
	
	g3.set_title(d.getStation());
	g3.set_style("points").plot_xy(x, y, "Coordenadas SGPS");
	g3.set_style("points").plot_xy(xreal, yreal, "Coordenadas Reales");
	
	Plotter::wait_for_key ();
}

void Plotter::histogram (vector<Coordinates> &errorPercent){
	
	Gnuplot g2, g3;
	vector<float> x,y;
	for(int i=0; i!=errorPercent.size(); i++){
		x.push_back(errorPercent[i].longitude);
		y.push_back(errorPercent[i].latitude);
	}
	float a[11]={0}, b[11]={0};
	float max1 = 0, max2 = 0;
	
	string ruta2 = "histogram_long.dat";
	string total;
	total = DirAnalyzer::createDir(ruta2);
	
	ofstream hist_long;
	hist_long.open(total.c_str());
	hist_long << "range\tcount" << endl;
	for(int i = 0; i != x.size(); i++){
		if(x[i] < 0)
			x[i]=x[i]*(-1);
		if(x[i] >=0 && x[i]<0.25)
			a[0]++;
		else if(x[i] >=0.25 && x[i]<0.5)
			a[1]++;
		else if(x[i] >=0.5 && x[i]<0.75)
			a[2]++;
		else if(x[i] >=0.75 && x[i]<1)
			a[3]++;
		else if(x[i] >=1 && x[i]<1.25)
			a[4]++;
		else if(x[i] >=1.25 && x[i]<1.5)
			a[5]++;
		else if(x[i] >=1.5 && x[i]<1.75)
			a[6]++;
		else if(x[i] >=1.75 && x[i]<2)
			a[7]++;
		else if(x[i] >=2 && x[i]<2.25)
			a[8]++;
		else if(x[i] >=2.25 && x[i]<2.5)
			a[9]++;
		else if(x[i] >=2.5 && x[i]<2.75)
			a[10]++;
		else if(x[i] >=2.75)
			a[11]++;
	}
	for (int n=0; n!=10; n++){
			hist_long << 0.25*n  << "\t" << a[n] <<  endl;//save the range and the times
			if (a[n] > max1)////look the max frequency, for the 'y' scale in the plot
				max1=a[n];
	}
	hist_long << "larger"  << "\t" << a[10]<<endl;
	
	hist_long.close();
	
	
	ruta2 = "histogram_lat.dat";
	total = DirAnalyzer::createDir(ruta2);
	ofstream hist_lat;
	hist_lat.open(total.c_str());
	hist_lat << "range\tcount" << endl;
	for(int s = 0; s != y.size(); s++){
		if(y[s] < 0)
			y[s]=y[s]*(-1);
		if(y[s] >=0 && y[s]<1)
			b[0]++;
		else if(y[s] >=1 && y[s]<2)
			b[1]++;
		else if(y[s] >=2 && y[s]<3)
			b[2]++;
		else if(y[s] >=3 && y[s]<4)
			b[3]++;
		else if(y[s] >=4 && y[s]<5)
			b[4]++;
		else if(y[s] >=5 && y[s]<6)
			b[5]++;
		else if(y[s] >=6 && y[s]<7)
			b[6]++;
		else if(y[s] >=7 && y[s]<8)
			b[7]++;
		else if(y[s] >=8 && y[s]<9)
			b[8]++;
		else if(y[s] >=9 && y[s]<10)
			b[9]++;
		else if(y[s] >=10 && y[s]<11)
			b[10]++;
		else if(y[s] >=11)
			b[11]++;
	}
	for (int m=0; m!=10; m++){
			hist_lat << m << "\t" << b[m] <<  endl;//save the range and the times
			if (b[m] > max2)////look the max frequency, for the 'y' scale in the plot
				max2=b[m];
	}
	hist_lat << "larger"  << "\t" << b[10]<<endl;
	
	hist_lat.close();
	
	
	
	g2.set_title("Histogram Percent Latitude");
	g2.set_yrange(0, max2+max2/4);//pongo una escala mayor
	g2.set_ylabel("Frequency");
	g2.set_xlabel("Latitude error (%)");
	g2.cmd("set boxwidth 0.8");
	g2.cmd("set style fill solid 0.8 border -1");
    g2.cmd("plot 'histogram_lat.dat' using 2:xtic(1) w boxes lc rgb 'blue' title 'Latitude'");
	
	
	g3.set_title("Histogram Percent Longitude");
	g3.set_yrange(0, max1+max1/4);//pongo un escala mayor
	g3.set_ylabel("Frequency");
	g3.set_xlabel("Longitude error (%)");
	g3.cmd("set boxwidth 0.8");
	g3.cmd("set style fill solid 0.8 border -1");
    g3.cmd("plot 'histogram_long.dat' using 2:xtic(1) w boxes lc rgb 'green' title 'Longitude'");
	
	
	//ofstream hist;
	//hist.open("../../output/histogram.dat");
	//hist << "longitude\tlatitude" << endl;
	//for(int i = 0; i != x.size(); i++){
		//if(x[i] < 0)
			//x[i]=x[i]*(-1);
		//if(y[i] < 0)
			//y[i]=y[i]*(-1);
		
		//hist << x[i] << "\t" << y[i] << endl;
	//}
	//hist.close();
	
	//g2.set_xautoscale();
	//g3.set_xautoscale();
	//g2.cmd("width = 0.1");
	//g3.cmd("width = 0.1");
	//g2.cmd("hist(x,width)=width*floor(x/width)+width/2.0");
	//g3.cmd("hist(x,width)=width*floor(x/width)+width/2.0");
	//g2.cmd("set boxwidth width*0.9");
	//g3.cmd("set boxwidth width*0.9");
	//g2.cmd("set style fill solid 0.5");
	//g3.cmd("set style fill solid 0.5");
	//g2.cmd("set xtics width");
	//g3.cmd("set xtics width");
	//g2.cmd("set xtic rotate by -60");
	//g3.cmd("set xtic rotate by -60");
	
	////g2.cmd("plot '../output/histogram.dat' using (hist($1,width)):(1.0) smooth freq w boxes title columnheader(1), '' u (hist($2,width)):(1.0) smooth freq w boxes ti columnheader(2)");
	//g2.cmd("plot '../../output/histogram.dat' using (hist($1,width)):(1.0) smooth freq w boxes title columnheader(1)");
	//g3.cmd("plot '../../output/histogram.dat' using (hist($2,width)):(1.0) smooth freq w boxes title columnheader(2)");
	
	
	Plotter::wait_for_key();


}

void Plotter::world (){
	
	Options * opt = Options::Instance();
	string p;
	p=opt -> getWorldPath ();
	p=p+"/world.dat";
	
	ifstream r;
	r.open(p.c_str());
	
	if (!r){
			Console::warning("World file not found");
	}
	else
		g1.set_style ("lines").plotfile_xy(p, 1, 2, "world");
	
}

void Plotter::wait_for_key ()
{
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__TOS_WIN__)  // every keypress registered, also arrow keys
    cout << endl << "Press any key to continue..." << endl;

    FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
    _getch();
#elif defined(unix) || defined(__unix) || defined(__unix__) || defined(__APPLE__)
    cout << endl << "Press ENTER to continue..." << endl;

    std::cin.clear();
    std::cin.ignore(std::cin.rdbuf()->in_avail());
    std::cin.get();
#endif
    return;
}
