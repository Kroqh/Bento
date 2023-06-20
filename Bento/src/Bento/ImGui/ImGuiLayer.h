#pragma once
#include "Bento/Layer.h"

namespace Bento {


	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();
		void OnAttach() override;
		void OnDeAttach()override;
		void OnUpdate() override;
		void OnEvent(Event& event) override;

	private:
		float m_Time = 0;
	};

}

