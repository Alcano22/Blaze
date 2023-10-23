#include "blzpch.h"
#include "OpenGLContext.h"

#include "Blaze/Core/Log.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Blaze
{
    OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
        : m_WindowHandle(windowHandle)
    {
        BLZ_CORE_ASSERT(windowHandle, "Window handle is null!")
    }

    void OpenGLContext::Init()
    {
        glfwMakeContextCurrent(m_WindowHandle);
        const int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        BLZ_CORE_ASSERT(status, "Failed to initialize Glad!")

        BLZ_CORE_INFO("OpenGL Info:");
        BLZ_CORE_INFO("  Vendor:   {0}", GLSTR_TO_CSTR(glGetString(GL_VENDOR)));
        BLZ_CORE_INFO("  Renderer: {0}", GLSTR_TO_CSTR(glGetString(GL_RENDERER)));
        BLZ_CORE_INFO("  Version:  {0}", GLSTR_TO_CSTR(glGetString(GL_VERSION)));
    }

    void OpenGLContext::SwapBuffers()
    {
        glfwSwapBuffers(m_WindowHandle);
    }

}
