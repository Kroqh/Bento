#pragma once


#ifdef BENTO_PLATFORM_WINDOWS

extern Bento::Application* Bento::CreateApplication();

int main(int argc, char** argv)
{
	auto app = Bento::CreateApplication();
	app->Run();
	delete app;
}

#else

#endif