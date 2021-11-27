#include <window_manager.hpp>
#include <cstdlib>
#include <iostream>

#if GUI_FEATURE_GLFW_WITH_IMGUI
	#include <imgui.h>
	#include <imgui_impl_glfw.h>
	#include <imgui_impl_opengl3.h>
	#include <glfw/glfw3.h>
#endif


namespace arm_simu{
	
	
	struct WinPointerImpl:public WinPointer{
		const void* unusual_header=nullptr;
		#if GUI_FEATURE_GLFW_WITH_IMGUI
			GLFWwindow* window;
			
		#endif
	};
	
	void WindowManager::Initialize(){
		#if GUI_FEATURE_GLFW_WITH_IMGUI
		//Initializing Glfw things with opengl 3.3
			glfwInit();
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		#endif
	}
	
	WinPointer* WindowManager::CreateWindow(const char* Title,const int X,const int Y,const int Width,const int Height){
		#if GUI_FEATURE_GLFW_WITH_IMGUI //When GUI feature is supported with glfw and imgui
			WinPointerImpl* window=new WinPointerImpl[1];
			window->window = glfwCreateWindow(Width, Height, Title, NULL, NULL);
			if (window == NULL)
			{
				std::cerr << "Failed to create GLFW window" << std::endl;
				glfwTerminate();
				exit(-1);
			}
			glfwMakeContextCurrent(window->window);
			glViewport(0, 0, 800, 800);
			
			// Initialize ImGUI
			IMGUI_CHECKVERSION();
			ImGui::CreateContext();
			ImGuiIO& io = ImGui::GetIO(); (void)io;
			ImGui::StyleColorsDark();
			ImGui_ImplGlfw_InitForOpenGL(window->window, true);
			ImGui_ImplOpenGL3_Init("#version 330");
			
			return reinterpret_cast<WinPointer*>(window);
		#endif
		
		return nullptr;
	}
	
	
	
	void WindowManager::DestroyWindow(WinPointer* _WinPointer){
		#if GUI_FEATURE_GLFW_WITH_IMGUI
			ImGui_ImplOpenGL3_Shutdown();
			ImGui_ImplGlfw_Shutdown();
			ImGui::DestroyContext();
			glfwDestroyWindow(((WinPointerImpl*)_WinPointer)->window);
		#endif
	}
	
	void WindowManager::StartWindow(WinPointer* _WinPointer,WinCallback callback){
		#if GUI_FEATURE_GLFW_WITH_IMGUI
			float size;
			bool drawTriangle;
			WinPointerImpl* winptr=reinterpret_cast<WinPointerImpl*>(_WinPointer);
			GLFWwindow* window=winptr->window;
			
			while (!glfwWindowShouldClose(window)){
				
				glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
				// Clean the back buffer and assign the new color to it
				glClear(GL_COLOR_BUFFER_BIT);

				// Tell OpenGL a new frame is about to begin
				ImGui_ImplOpenGL3_NewFrame();
				ImGui_ImplGlfw_NewFrame();
				ImGui::NewFrame();
				
				
				ImGui::Begin("My name is window, ImGUI window");
				// Text that appears in the window
				ImGui::Text("Hello there adventurer!");
				// Checkbox that appears in the window
				ImGui::Checkbox("Draw Triangle", &drawTriangle);
				// Slider that appears in the window
				ImGui::SliderFloat("Size", &size, 0.5f, 2.0f);
				// Fancy color editor that appears in the window
				
				callback(_WinPointer);
				
				
				ImGui::End();
				// Renders the ImGUI elements
				ImGui::Render();
				ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

				// Swap the back buffer with the front buffer
				glfwSwapBuffers(window);
				// Take care of all GLFW events
				glfwPollEvents();
			}
			
		#endif
	}
	
	void WindowManager::Finalize(){
		#if GUI_FEATURE_GLFW_WITH_IMGUI
			glfwTerminate();
		#endif
	}
}