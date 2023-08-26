#include <Bento.h>
#include "Bento/Core/EntryPoint.h"

#include "EditorLayer.h"

class BentoEditor : public Bento::Application
{
public:
	BentoEditor()
		: Application("Bento Editor")
	{
		//PushLayer(new ExampleLayer());
		PushLayer(new Bento::EditorLayer());
	}
	~BentoEditor() {

	}
};

Bento::Application* Bento::CreateApplication() {
	return new BentoEditor();
}