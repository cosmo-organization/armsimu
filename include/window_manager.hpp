#pragma once


namespace arm_simu{
	typedef void* Extra;
	struct WinPointer{const void* unusual_header=nullptr;};
	struct Widget{const void* unusual_header=nullptr;};
	typedef void(*WinCallback)(WinPointer*,Extra);
	class WindowManager{
		public:
			static void Initialize();
			static WinPointer* CreateWindow(const char* Title,const int X,const int Y,const int Width,const int Height);
			static void DestroyWindow(WinPointer* _WinPointer);
			static void StartWindow(WinPointer* _WinPointer,WinCallback callback,Extra extra=nullptr);
			static void Finalize();
			static float DeltaTime();
	};
}