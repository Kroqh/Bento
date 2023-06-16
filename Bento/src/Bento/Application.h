#pragma once
#include "Core.h"

namespace Bento{

class BENTO_API Application
{
public:
	Application();
	virtual ~Application();

	void Run();
};

// To be defined in client
Application* CreateApplication();

}

