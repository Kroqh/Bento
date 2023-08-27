#include <Bento.h>
#include "Bento/Core/EntryPoint.h"

#include "Bento/Platform/OpenGL/OpenGLShader.h"

#include "imgui/imgui.h"

#include <glm/gtc/type_ptr.hpp>

#include "Sandbox2D.h"

class Sandbox : public Bento::Application
{
public:
	Sandbox() {
		//PushLayer(new ExampleLayer());
		PushLayer(new Sandbox2D());
	}
	~Sandbox() {

	}
};

Bento::Application* Bento::CreateApplication() {
	return new Sandbox();
}