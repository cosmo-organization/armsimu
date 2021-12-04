#pragma once
#include <armadillo>
#include <window_manager.hpp>

//Experimental 
namespace ImPlot{
	void ShowDemo_Heatmaps();
	void ShowDemo_Help();
	void ShowDemo_Config();
	void ShowDemo_DigitalPlots();
	void ShowDemoWindow(bool* open);
}

namespace arm_simu{
	
	class Plot{
		static void PlotterCallback(arm_simu::WinPointer*,arm_simu::Extra);
		public:
			static void LinePlot(arma::vec x,arma::vec y,const char* title);
	};
	
}