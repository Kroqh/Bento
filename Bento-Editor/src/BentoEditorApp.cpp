#include <Bento.h>
#include "Bento/Core/EntryPoint.h"

#include "EditorLayer.h"

namespace Bento {

	class BentoEditor : public Application
	{
	public:
		BentoEditor(ApplicationSpecification& spec)
			: Application(spec)
		{
			PushLayer(new EditorLayer());
		}
		~BentoEditor() {

		}
	};

	Application* CreateApplication(ApplicationCommandLineArgs args) {
		ApplicationSpecification spec;
		spec.Name = "BentoEditor";
		spec.CommandLineArgs = args;

		return new BentoEditor(spec);
	}
}