#pragma once

struct GLFWwindow;

namespace Engine {

	struct EWindowProp
	{
		EWindowProp(const EString& title, uint width, uint height)
			: title(title), width(width), height(height)
		{}
		EString title;
		uint width;
		uint height;
	};

	class EWindow
	{
	public:
		EWindow(const EWindowProp&  prop);
		~EWindow();

		inline GLFWwindow* GetNativeWindow() const { return fWindow; }

		void Update() const;
		bool IsClosed() const;

		inline const uint GetWidth() const { return fData.width; }
		inline const uint GetHeight() const { return fData.height; }
	private:
		GLFWwindow* fWindow;

		struct EWindowData
		{
			EString title;
			uint width;
			uint height;
			// EVENT CALLBACK FUCNITON
		};
		EWindowData fData;
	};

}