#include <Bento.h>
#include <Bento/Core/EntryPoint.h>

#include "Sandbox2D.h"

class Sandbox : public Bento::Application
{
public:
	Sandbox(const Bento::ApplicationSpecification& specification)
		: Bento::Application(specification)
	{
		// PushLayer(new ExampleLayer());
		PushLayer(new Sandbox2D());
	}

	~Sandbox()
	{
	}
};

Bento::Application* Bento::CreateApplication(Bento::ApplicationCommandLineArgs args)
{
	ApplicationSpecification spec;
	spec.Name = "Sandbox";
	spec.WorkingDirectory = "../Bentonut";
	spec.CommandLineArgs = args;

	return new Sandbox(spec);
}