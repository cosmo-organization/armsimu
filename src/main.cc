#include <iostream>
#include <armadillo>
#include <armsimu.hpp>
#include <vector>
#include <cmath>
#include <utility>
#include <system.hpp>
#include <window_manager.hpp>
#include <implot/implot.h>
#include <plotter.hpp>

void model(arma::rowvec y,double t,arma::rowvec& dydt){
	dydt[0]=2*t*t;
	dydt[1]=2*t*t;
}

void model2(double y,double t,double& dydt){
	double k=0.3;
	dydt=-k*y;
}

void velocity_model(double y,double t,double& dydt){
	dydt=2*t*t;
}

arma::vec arange(double start,double end,double step){
	arma::vec result(int(end/step)-int(start/step));
	int ctr=0;
	for (double t=start;t<end;t+=step){
		result[ctr++]=t;
	}
	return result;
}


void input(double t,arma::vec* result){
	(*result)[0]=10;
}

double* ptr;
double* time_ptr;
int size=0;

void WinCallBacks(arm_simu::WinPointer*,arm_simu::Extra extra){
	
    if (ImPlot::BeginPlot("Scatter Plot")) {
        ImPlot::PlotScatter("Data 1", time_ptr, ptr, size);
        ImPlot::PushStyleVar(ImPlotStyleVar_FillAlpha, 0.1f);
        ImPlot::SetNextMarkerStyle(ImPlotMarker_Square, 1, ImPlot::GetColormapColor(1), IMPLOT_AUTO, ImPlot::GetColormapColor(1));
        ImPlot::PopStyleVar();
        ImPlot::EndPlot();
    }
	
	
}

int main(const int argc,const char** argv){
	
		arma::vec t_frame=arange(0,1000+0.01,0.01);
		arma::rowvec y0(2);
		double dy0=0;
		y0[0]=0;
		y0[1]=0;
		constexpr double M=10;
		constexpr double K=1;
		constexpr double Damp=0.01;
		double KbyM=K/M;
		double oneByM=1/M;
		double BbyM=Damp/M;
		
		arma::mat A(2,2);
		A.at(0,0)=0;
		A.at(0,1)=1;
		A.at(1,0)=-KbyM;
		A.at(1,1)=-BbyM;
		
		arma::mat B(2,1);
		B.at(0,0)=0;
		B.at(1,0)=oneByM;
		
		arma::mat C(0,0);
		arma::mat D(0,0);
		arm_simu::System _system(A,B,C,D,y0,(arm_simu::input_handle)input,1);
		auto result=_system.compute_state(t_frame);
		
	{
		arm_simu::WindowManager::Initialize();
		
		arm_simu::Plot::ScatterPlot(t_frame,result.col(0),"Scatter Plot Example");
		
		arm_simu::WindowManager::Finalize();
		
	}
	
	return 0;
}
