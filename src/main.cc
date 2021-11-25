#include <iostream>
#include <armadillo>
#include <armsimu.hpp>
#include <vector>
#include <cmath>
#include <utility>

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



int main(const int argc,const char** argv){
	
	{
		arma::vec t_frame=arange(0,2+0.1,0.1);
		arma::rowvec y0(2);
		double dy0=0;
		y0[0]=0;
		y0[1]=0;
		auto result=arm_simu::EulerIntegrate(model,y0,t_frame);
		result.first.print("Compared");
		auto result1=arm_simu::EulerIntegrate(velocity_model,dy0,t_frame);
		result1.first.print("Later");
		
		//t_frame.print("TimeFrame");
	}
	
	
	return 0;
}
