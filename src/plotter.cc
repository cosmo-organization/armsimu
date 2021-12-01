#include <plotter.hpp>


namespace arm_simu{
		struct PlotArg{
			double* x;
			arma::uword size_x;
			double* y;
			arma::uword size_y;
		};
		
		void Plot::PlotterCallback(arm_simu::WinPointer* ptr,arm_simu::Extra extra){
			PlotArg* arg=reinterpret_cast<PlotArg*>(extra);
			 if (ImPlot::BeginPlot("Scatter Plot")) {
				ImPlot::PlotLine("Result",arg->x,arg->y,arg->size_x,0,2*sizeof(float));				
			}
			ImPlot::EndPlot();
		}
		
		void Plot::ScatterPlot(arma::vec x,arma::vec y,const char* title){
			arm_simu::WinPointer* plotWindow=arm_simu::WindowManager::CreateWindow(title,0,0,800,600);
			ImPlotContext* context=ImPlot::CreateContext();
			ImPlot::SetCurrentContext(context);
			PlotArg* arg=new PlotArg{x.memptr(),x.size(),y.memptr(),y.size()};
			ImPlot::GetStyle().AntiAliasedLines=true;
			arm_simu::WindowManager::StartWindow(plotWindow,Plot::PlotterCallback,(void*)arg);
			arm_simu::WindowManager::DestroyWindow(plotWindow);
			ImPlot::DestroyContext(context);
			delete[] plotWindow;
			delete[] arg;
		}
		
	
}