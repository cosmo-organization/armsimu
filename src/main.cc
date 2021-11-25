#include <iostream>
#include <armadillo>
#include <armsimu.hpp>
#include <vector>
#include <cmath>
#include <utility>
#include <system.hpp>

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
	(*result)[0]=0.001;
}
int main(const int argc,const char** argv){
	
	{
		arma::vec t_frame=arange(0,1000+0.01,0.01);
		arma::rowvec y0(2);
		double dy0=0;
		y0[0]=5;
		y0[1]=0;
		constexpr double M=1;
		constexpr double K=0.1;
		constexpr double Damp=0;
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
		result.print();
		//t_frame.print("TimeFrame");
	}
	
	
	return 0;
}
