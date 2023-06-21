#include <Bento.h>

class ExampleLayer : public Bento::Layer {

public:
	ExampleLayer()
		: Layer("Example") {}
	 
	void OnUpdate() override{

		if (Bento::Input::IsKeyPressed(Bento::Key::H)) {

			BENTO_TRACE("Pressed H!");

		}

	}
	void OnEvent(Bento::Event& event) override {

	}
};

class Sandbox : public Bento::Application
{
public:
	Sandbox() {
		PushLayer(new ExampleLayer());
		PushOverlay(new Bento::ImGuiLayer());
	}
	~Sandbox() {

	}
};

Bento::Application* Bento::CreateApplication() {
	return new Sandbox();
}