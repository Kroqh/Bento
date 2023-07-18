#pragma once


#ifdef BENTO_PLATFORM_WINDOWS

extern Bento::Application* Bento::CreateApplication();

int main(int argc, char** argv)
{
	Bento::Log::Init();

	BENTO_PROFILE_BEGIN_SESSION("Startup", "BentoProfile-Startup.json");
	auto app = Bento::CreateApplication();
	BENTO_PROFILE_END_SESSION();

	BENTO_PROFILE_BEGIN_SESSION("Runtime", "BentoProfile-Runtime.json");
	app->Run();
	BENTO_PROFILE_END_SESSION();

	BENTO_PROFILE_BEGIN_SESSION("Shutdown", "BentoProfile-Shutdown.json");
	delete app;
	BENTO_PROFILE_END_SESSION();

}

#else

#endif