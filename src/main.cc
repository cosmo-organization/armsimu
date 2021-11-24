#include <iostream>
#include <armadillo>
#include <armsimu.hpp>
#include <vector>
#include <cmath>
#include <utility>

void model(arma::vec y,double t,arma::vec& dydt){
	dydt[0]=3*y[1]*t;
	dydt[1]=2*t*y[0];
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
		arma::mat mn(2000,2000);
		mn.fill(1);
		arma::vec result(mn.n_cols);
		std::cout<<"Here is ok"<<std::endl;
		arm_simu::KahanSum::Summation(mn,&result);
	}
	
	return 0;
}
