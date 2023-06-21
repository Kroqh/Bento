#include <Bento.h>

#include "imgui/imgui.h"


class ExampleLayer : public Bento::Layer {

public:
	ExampleLayer()
		: Layer("Example") {
	

	}
	 
	void OnUpdate() override{

	}

	virtual void OnImGuiRender() override {

		ImGui::Begin("Test");
		ImGui::Text("Hello World!");
		ImGui::End();

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
	}
	~Sandbox() {

	}
};

Bento::Application* Bento::CreateApplication() {
	return new Sandbox();
}