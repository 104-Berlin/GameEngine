#pragma once

namespace Engine {

	

	class EMainWindow
	{
	private:
		u32 fWidth;
		u32 fHeight;
		EString fTitle;

		void* fNativeWindowPtr;
	public:
		EMainWindow(const EString& title, u32 width, u32 height);
		~EMainWindow();

		void PollEvent();
		void Update();
		void Present();
		bool IsOpen();
	private:
		void Init();
	};

}
