#include "Bentopch.h"
#include "Bento/Core/Window.h"

#ifdef BENTO_PLATFORM_WINDOWS
#include "Bento/Platform/Windows/WindowsWindow.h"
#endif

namespace Bento
{
	Scope<Window> Window::Create(const WindowProps& props)
	{
#ifdef BENTO_PLATFORM_WINDOWS
		return CreateScope<WindowsWindow>(props);
#else
		BENTO_CORE_ASSERT(false, "Unknown platform!");
		return nullptr;
#endif
	}

}