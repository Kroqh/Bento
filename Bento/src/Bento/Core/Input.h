#pragma once
#include "Bento/Core/Core.h"

namespace Bento {

	class BENTO_API Input
	{
	public:
		static bool IsKeyPressed(int keycode) { return s_Instacne->IsKeyPressedImpl(keycode); };

		static bool IsMouseButtonPressed(int button) { return s_Instacne->IsMouseButtonPressedImpl(button); };
		static  std::pair<float, float> GetMousePosition() { return s_Instacne->GetMousePositionImpl(); };
		static float GetMouseX() { return s_Instacne->GetMouseXImpl(); };
		static float GetMouseY() { return s_Instacne->GetMouseYImpl(); };

	protected:
		virtual bool IsKeyPressedImpl(int keycode) = 0;
		virtual bool IsMouseButtonPressedImpl(int button) = 0;
		virtual  std::pair<float, float> GetMousePositionImpl() = 0;
		virtual float GetMouseXImpl() = 0;
		virtual float GetMouseYImpl() = 0;

	private:
		static Input* s_Instacne;
	};
}