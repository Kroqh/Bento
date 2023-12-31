#pragma once

#include "Bento/Core/Window.h"
#include "Bento/Renderer/GraphicsContext.h"

#include <GLFW/glfw3.h>


namespace Bento {

	class WindowsWindow : public Window
	{

	public:
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

		void OnUpdate() override;

		inline unsigned int GetWidth() const override { return m_Data.Width; }
		inline unsigned int GetHeight() const override { return m_Data.Height; }
		inline virtual void* GetNativeWindow() const override { return m_Window; }

		// Window attributes

		inline void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }
		void SetVSync(bool enabled) override;
		bool IsVSync() const override;

	private:
		virtual void Init(const WindowProps& porps);
		virtual void Shutdown();
	private:
		GLFWwindow* m_Window;
		GraphicsContext* m_Context;

		struct WindowData {

			std::string Title;
			unsigned int Width, Height;
			bool VSync;

			EventCallbackFn EventCallback;

		};

		WindowData m_Data;
	};

}



