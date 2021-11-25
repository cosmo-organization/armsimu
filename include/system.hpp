#pragma once
#include <armadillo>
#include <iostream>

namespace arm_simu{
	
	typedef void (*input_handle)(double t,arma::vec*);
	
	class System{
		arma::mat A;
		arma::mat B;
		arma::mat C;
		arma::mat D;
		arma::rowvec x0;
		arma::rowvec x0_copy;
		input_handle handle;
		int input_size;
		public:
			System(arma::mat A,arma::mat B,arma::mat C,arma::mat D,arma::rowvec x0,input_handle handle,int input_size);
			~System();
			arma::mat& getA();
			arma::mat& getB();
			arma::mat& getC();
			arma::mat& getD();
			arma::rowvec& getX0();
			arma::mat compute_state(arma::vec t_frame);
			arma::mat compute_output(arma::mat state_result);//to be implement
		private:
	};
	
}