#pragma once
#include "Core.h"

#include "Window.h"
#include "Bento/LayerStack.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "Events/KeyEvent.h"

#include "Bento/ImGui/ImGuiLayer.h"

#include "Bento/Renderer/Shader.h"
#include "Bento/Renderer/Buffer.h"
#include "Bento/Renderer/VertexArray.h"

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
	bool OnWindowCloseKey(KeyPressedEvent& e);
	std::unique_ptr<Window> m_Window;
	ImGuiLayer* m_ImGuiLayer;
	bool m_Running = true;
	LayerStack m_LayerStack;

	std::shared_ptr<VertexArray> m_VertexArray;
	std::shared_ptr<Shader> m_Shader;

	std::shared_ptr<VertexArray> m_SquareVA;
	std::shared_ptr<Shader> m_Shader2;
private:
	static Application* s_Instance;
};

// To be defined in client
Application* CreateApplication();

}

