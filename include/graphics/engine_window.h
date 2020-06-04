#pragma once

struct GLFWwindow;

namespace Engine {

	struct EWindowProp
	{
		EWindowProp(const EString& title, u32 width, u32 height)
			: title(title), width(width), height(height)
		{}
		EString title;
		u32 width;
		u32 height;
	};

	class EWindow
	{
	public:
		EWindow(const EWindowProp&  prop);
		~EWindow();

		inline GLFWwindow* GetNativeWindow() const { return fWindow; }

		void Update() const;
		bool IsClosed() const;

		inline const u32 GetWidth() const { return fData.width; }
		inline const u32 GetHeight() const { return fData.height; }
	private:
		GLFWwindow* fWindow;

		struct EWindowData
		{
			EString title;
			u32 width;
			u32 height;
			// EVENT CALLBACK FUCNITON
		};
		EWindowData fData;
	};

}