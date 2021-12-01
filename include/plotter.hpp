#pragma once
#include <armadillo>
#include <window_manager.hpp>
#include <implot/implot.h>
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
			static void ScatterPlot(arma::vec x,arma::vec y,const char* title);
	};
	
}