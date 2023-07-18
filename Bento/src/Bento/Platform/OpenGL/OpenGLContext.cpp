#include "Bentopch.h"
#include "OpenGLContext.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Bento {



	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		BENTO_CORE_ASSERT(windowHandle, "Window handle is null!")
	}

	void OpenGLContext::Init()
	{
		BENTO_PROFILE_FUNCTION();

		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		BENTO_CORE_ASSERT(status, "Failed to initialize Glad!");

		
		
		BENTO_CORE_INFO("OpenGL Info:");
		BENTO_CORE_INFO("	Vendor: {0}", (const char*)glGetString(GL_VENDOR));
		BENTO_CORE_INFO("	Renderer: {0}", (const char*)glGetString(GL_RENDERER));
		BENTO_CORE_INFO("	Version: {0}", (const char*)glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers()
	{
		BENTO_PROFILE_FUNCTION();

		glfwSwapBuffers(m_WindowHandle);
	}

}