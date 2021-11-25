#include <system.hpp>

namespace arm_simu{
	
	
	
	System::System(arma::mat A,arma::mat B,arma::mat C,arma::mat D,arma::rowvec x0,input_handle handle,int input_size){
		this->A=A;
		this->B=B;
		this->C=C;
		this->D=D;
		this->x0=x0;
		this->handle=handle;
		this->input_size=input_size;
		this->x0_copy=x0;
	}
	
	System::~System(){
		
	}
	
	arma::mat System::compute_state(arma::vec t_frame){
		x0=x0.as_row();
		double dt=t_frame[1]-t_frame[0];
		arma::mat _result(t_frame.size(),x0.size());
		_result.row(0)=x0;
		arma::vec input(input_size);
		handle(t_frame[0],&input);
		for (int i=1;i<t_frame.size();i++){
			auto slope=A*(_result.row(i-1).as_col())+B*input;
			_result.row(i)=_result.row(i-1)+(dt*slope).as_row();
			handle(t_frame[i],&input);
		}
		
		return _result;
	}
	
	arma::mat System::compute_output(arma::mat state_result){
		arma::mat _result(0,0);
		
		
		return _result;
	}
	
	arma::mat& System::getA(){
		return A;
	}
	arma::mat& System::getB(){
		return B;
	}
	arma::mat& System::getC(){
		return C;
	}
	arma::mat& System::getD(){
		return D;
	}
	arma::rowvec& System::getX0(){
		return x0_copy;
	}
	
}