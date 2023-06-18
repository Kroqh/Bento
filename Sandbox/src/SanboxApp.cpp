#include <Bento.h>


class ExampleLayer : public Bento::Layer {

public:
	ExampleLayer()
		: Layer("Example") {}
	 
	void OnUpdate() override{

		BENTO_INFO("ExampleLayer::Update");

	}
	void OnEvent(Bento::Event& event) override {

		BENTO_TRACE("{0}", event);

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