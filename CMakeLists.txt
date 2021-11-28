cmake_minimum_required(VERSION 3.10)
project(armasimu VERSION 1.0)

add_compile_definitions(GUI_FEATURE_GLFW_WITH_IMGUI)

add_subdirectory("dep/glfw")

include_directories(
	"dep" "include" 
	"dep/imgui/backends/" "dep/imgui")


add_executable(armasimu 
	"src/main.cc" "src/system.cc" "src/window_manager.cc"
	"dep/imgui/imgui.cpp" "dep/imgui/imgui_demo.cpp"
	"dep/imgui/imgui_draw.cpp" "dep/imgui/imgui_tables.cpp"
	"dep/imgui/imgui_widgets.cpp" "dep/imgui/backends/imgui_impl_glfw.cpp"
	"dep/imgui/backends/imgui_impl_opengl3.cpp" "dep/implot/implot.cpp"
	"dep/implot/implot_items.cpp"
	)

target_link_libraries(armasimu PUBLIC glfw opengl32 dep/linker/armadillo dep/linker/blas_win64_MT dep/linker/lapack_win64_MT)
