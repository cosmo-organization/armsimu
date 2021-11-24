#include <iostream>
#include <armadillo>
#include <armsimu.hpp>
#include <vector>
#include <cmath>
#include <utility>

void model(arma::rowvec y,double t,arma::rowvec& dydt){
	dydt[0]=-0.3*y[0];
	dydt[1]=-0.3*y[1];
}

void model2(double y,double t,double& dydt){
	double k=0.3;
	dydt=-k*y;
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
		arma::vec t_frame=arange(0,1,0.01);
		arma::rowvec y0(2);
		double dy0=10;
		y0[0]=10;
		y0[1]=10;
		auto result=arm_simu::EulerIntegrate(model,y0,t_frame);
		result.first.print();
		auto result1=arm_simu::EulerIntegrate(model2,dy0,t_frame);
		result1.first.print("Later");
		
		t_frame.print("TimeFrame");
	}
	
	
	return 0;
}
