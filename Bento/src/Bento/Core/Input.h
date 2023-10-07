#pragma once
#include "Bento/Core/Core.h"
#include "KeyCodes.h"
#include "MouseCodes.h"
namespace Bento {

	class  Input
	{
	public:
		static bool IsKeyPressed(KeyCode key);
		static bool IsKeyDown(KeyCode keycode);
		static bool IsKeyUp(KeyCode keycode);

		static bool IsMouseButtonPressed(MouseCode button);
		static bool IsMouseButtonDown(MouseCode button);
		static bool IsMouseButtonUp(MouseCode button);

		static glm::vec2 GetMousePosition();
		static float GetMouseX();
		static float GetMouseY();

	protected:
		static bool GetKey(KeyCode keycode);
		static bool GetMouseButton(MouseCode mousecode);

	private:
		friend class Application;

		static void OnUpdate();
	};
}