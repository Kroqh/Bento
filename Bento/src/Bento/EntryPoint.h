#pragma once


#ifdef BENTO_PLATFORM_WINDOWS

extern Bento::Application* Bento::CreateApplication();

int main(int argc, char** argv)
{
	Bento::Log::Init();
	BENTO_CORE_WARN("Initialized Log!");
	int a = 5;
	BENTO_INFO("Hello! Var={0}", a);

	auto app = Bento::CreateApplication();
	app->Run();
	delete app;
}

#else

#endif