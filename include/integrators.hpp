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
	static std::pair<arma::vec,arma::vec> EulerIntegrate(
		typename IntegralPointerBuilder<double>::Pointer equation,double x0,arma::vec t_frame
	){
		double dt=t_frame[1]-t_frame[0];
		std::pair<arma::vec,arma::vec> result;
		result.second=t_frame;
	
		arma::vec _result(t_frame.size());
		KahanSumParam<double> param;
		_result[0]=x0;
		for (int i=1;i<t_frame.size();i++){
			double slope;
			equation(_result[i-1],t_frame[i-1],slope);
			
			param.sum=_result[i-1];
			_result[i]=KahanSum::StepSummation<double>(dt*slope,param);
			
			//KahanSum::ResetStepSummation(param);
		}
		result.first=_result;
		
		return result;
	}
	
	
	static std::pair<arma::mat,arma::vec> EulerIntegrate(
		typename IntegralPointerBuilder<arma::rowvec>::Pointer equation,arma::rowvec x0,arma::vec t_frame
	){
		std::pair<arma::mat,arma::vec> result;
		
		result.second=t_frame;
		double dt=t_frame[1]-t_frame[0];
		
		arma::mat _result(t_frame.size(),x0.size());
		
		arm_simu::KahanSumParam<arma::rowvec> param{
			x0,
			arma::rowvec(x0.size()),
			arma::rowvec(x0.size()),
			arma::rowvec(x0.size())
		};
		param.y.fill(0);
		param.t.fill(0);
		param.c.fill(0);
		_result.row(0)=x0;
		arma::rowvec slope(x0.size());
		for (int i=1;i<t_frame.size();i++){
			
			equation(_result.row(i-1),t_frame[i-1],slope);
			
			_result.row(i)=_result.row(i-1)+dt*slope;
			param.sum=_result.row(i-1);
		}
		
		
		result.first=_result;
		
		return result;
	}
	
}