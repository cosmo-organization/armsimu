#pragma once
#include <iostream>
#include <vector>
#include <armadillo>
#include <thread>

namespace arm_simu{
	
	template<typename T>
	struct KahanSumParam{
		T sum=0;
		T c=0;
		T y=0;
		T t=0;
	};
	
	template<typename T>
	std::ostream& operator<<(std::ostream& cout,KahanSumParam<T> param){
		cout<<"KahanSumParam[sum:"<<param.sum<<", c:"<<param.c<<", y:"<<param.y<<", t:"<<param.t<<"]";
		return cout;
	}
	
	class KahanSum{
		
		private:
			static void ThreadWorkerSummation(double* input,const int size,arma::vec* out,const int index,bool use_kahansum=true){
				if (use_kahansum){
					double sum=0;
					double c=0;
					for (unsigned long long i=0;i<size;i++){
						double y=input[i]-c;
						double t=sum+y;
						c=(t-sum)-y;
						sum=t;
					}
					(*out)[index]=sum;
				}else{
					double sum=0;
					for (int i=0;i<size;i++){
						sum+=input[i];
					}
					(*out)[index]=sum;
				}
			}
		
		public:
			//full Summation use_kahansum=true(for kahansummation) and false for normal summation @param arma::vec
			template<typename T>
			static T Summation(arma::vec input,bool use_kahansum=true){
				if (use_kahansum){
					T sum=0;
					T c=0;
					for (unsigned long long i=0;i<input.size();i++){
						T y=input[i]-c;
						T t=sum+y;
						c=(t-sum)-y;
						sum=t;
					}
					return sum;
				}else{
					T sum=0;
					for (int i=0;i<input.size();i++){
						sum+=input[i];
					}
					return sum;
				}
				return 0;
			}
			
			static void Summation(arma::mat input,arma::vec* result,bool use_kahansum=true){
				arma::uword ncols=input.n_cols;
				arma::uword nrows=input.n_rows;
				
				if (ncols<=2000){
				
					std::thread* thread_list=new std::thread[ncols];
					for (int i=0;i<ncols;i++){
						double* ptr=input.colptr(i);
						thread_list[i]=std::thread(ThreadWorkerSummation,input.colptr(i),nrows,result,i,use_kahansum);
					}
					
					for (int i=0;i<ncols;i++){
						thread_list[i].join();
					}
					
					delete[] thread_list;
				}else{
					throw std::runtime_error("columns must be in range of [0,2000]");
				}
			}
			
			//full Summation use_kahansum=true(for kahansummation) and false for normal summation @param std::vec
			template<typename T>
			static T Summation(std::vector<T> input,bool use_kahansum=true){
				if (use_kahansum){
					T sum=0;
					T c=0;
					for (unsigned long long i=0;i<input.size();i++){
						T y=input[i]-c;
						T t=sum+y;
						c=(t-sum)-y;
						sum=t;
					}
					return sum;
				}else{
					T sum=0;
					for (int i=0;i<input.size();i++){
						sum+=input[i];
					}
					return sum;
				}
				return 0;
			}
			//Step kahansummation
			template<typename T>
			static T StepSummation(T i_input,KahanSumParam<T>& param){
				param.y=i_input-param.c;
				param.t=param.sum+param.y;
				param.c=(param.t-param.sum)-param.y;
				param.sum=param.t;
				return param.sum;
			}
			
			template<typename T>
			static arma::vec StepSummation(arma::mat input,std::vector<KahanSum<T>>& params){
				
			}
			
			//Reseting to recompute stepsummation
			template<typename T>
			static void ResetStepSummation(KahanSumParam<T>& param){
				param.sum=0;
				param.y=0;
				param.c=0;
				param.t=0;
			}
			
	};
}