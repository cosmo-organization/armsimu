#pragma once
#include <utility>
#include <armadillo>
#include <kahansum.hpp>
#include <utility.hpp>

namespace arm_simu{
	
	template<typename RPType>
	struct IntegralPointerBuilder{
		typedef void (*Fptr)(RPType y,double t,RPType& dydt);
		typedef Fptr Pointer;
	};
	
	//These returns matrix and time vector
	template<typename T>
	static std::pair<arma::vec,arma::vec> EulerIntegrate(
		typename IntegralPointerBuilder<T>::Pointer equation,T x0,arma::vec t_frame
	){
		double dt=t_frame[1]-t_frame[0];
		std::pair<arma::vec,arma::vec>::type,arma::vec> result;
		result.second=t_frame;
	
		arma::vec _result(t_frame.size());
		KahanSumParam<double> param;
		_result[0]=x0;
		for (double i=1;i<t_frame.size();i++){
			double slope;
			equation(_result[i-1],t_frame[i-1],slope);
			
			param.sum=_result[i-1];
			_result[i]=KahanSum::StepSummation<T>(dt*slope,param);
			
			KahanSum::ResetStepSummation(param);
		}
		result.first=_result;
		
		return result;
	}
}