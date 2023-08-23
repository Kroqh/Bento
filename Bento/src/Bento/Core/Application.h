#pragma once
#include "Core.h"

#include "Window.h"
#include "Bento/Core/LayerStack.h"
#include "Bento/Events/Event.h"
#include "Bento/Events/ApplicationEvent.h"
#include "Bento/Events/KeyEvent.h"

#include "Bento/ImGui/ImGuiLayer.h"

#include "Bento/Renderer/Shader.h"
#include "Bento/Renderer/Buffer.h"
#include "Bento/Renderer/VertexArray.h"

#include "Bento/Renderer/OrthographicCamera.h"

#include "Bento/Core/Timestep.h"

namespace Bento{

class BENTO_API Application
{
public:
	Application();
	virtual ~Application();

	void Run();

	void OnEvent(Event& e);

	void PushLayer(Layer* layer);
	void PushOverlay(Layer* overlay);

	inline Window& GetWindow() { return *m_Window; }
	inline static Application& Get() { return *s_Instance; }

private:
	bool OnWindowClose(WindowCloseEvent& e);
	bool OnWindowResize(WindowResizeEvent& e);
	bool OnWindowCloseKey(KeyPressedEvent& e);

private:
	Scope<Window> m_Window;
	ImGuiLayer* m_ImGuiLayer;
	bool m_Running = true;
	bool m_Minimized = false;
	LayerStack m_LayerStack;
	float m_LastFrameTime = 0.0f;

	
private:
	static Application* s_Instance;
};

// To be defined in client
Application* CreateApplication();

}
