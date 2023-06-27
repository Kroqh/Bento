#pragma once

#include "Bento/Core.h"
#include "Bento/Events/Event.h"
#include "Bento/Core/Timestep.h"

namespace Bento {

	class BENTO_API Layer
	{
	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() {}
		virtual void OnDeAttach() {}
		virtual void OnUpdate(Timestep ts) {}
		virtual void OnImGuiRender() {};
		virtual void OnEvent(Event& event) {}

		inline const std::string& GetNAme() const { return m_DebugName; }

	protected:
		std::string m_DebugName;
	};

}



