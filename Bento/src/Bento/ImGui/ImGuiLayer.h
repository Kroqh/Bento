#pragma once
#include "Bento/Core/Core.h"
#include "Bento/Core/Layer.h"
#include "Bento/Events/KeyEvent.h"
#include "Bento/Events/MouseEvent.h"
#include "Bento/Events/ApplicationEvent.h"

namespace Bento {


	class BENTO_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();
		virtual void OnAttach() override;
		virtual void OnDeAttach() override;
		virtual void OnImGuiRender() override;

		void Begin();
		void End();


	private:
		float m_Time = 0;
	};

}

