#include <Bento.h>

class ExampleLayer : public Bento::Layer {

public:
	ExampleLayer()
		: Layer("Example") {}
	 
	void OnUpdate() override{

	}
	void OnEvent(Bento::Event& event) override {

		if (event.GetEventType() == Bento::EventType::KeyPressed) {

			Bento::KeyPressedEvent& e = (Bento::KeyPressedEvent&)event;

			if (e.GetKeyCode() == Bento::Key::H && e.GetRepeatCount() == 0) {
				BENTO_TRACE("{0}", (char)e.GetKeyCode());
			}

		}

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