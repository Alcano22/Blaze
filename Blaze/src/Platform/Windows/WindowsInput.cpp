#include "blzpch.h"
#include "WindowsInput.h"

#include "Blaze/Core/Application.h"

#include <GLFW/glfw3.h>

namespace Blaze
{
    Input* Input::s_Instance = new WindowsInput();
    
    bool WindowsInput::IsKeyPressedImpl(const int keycode)
    {
        const auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
        const auto state = glfwGetKey(window, keycode);
        return state == GLFW_PRESS || state == GLFW_REPEAT;
    }

    bool WindowsInput::IsMouseButtonPressedImpl(const int button)
    {
        const auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
        const auto state = glfwGetMouseButton(window, button);
        return state == GLFW_PRESS;
    }

    std::pair<float, float> WindowsInput::GetMousePosImpl()
    {
        const auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
        double posX, posY;
        glfwGetCursorPos(window, &posX, &posY);

        return { (float)posX, (float)posY };
    }

    float WindowsInput::GetMouseXImpl()
    {
        auto[x, y] = GetMousePosImpl();
        return x;
    }

    float WindowsInput::GetMouseYImpl()
    {
        auto[x, y] = GetMousePosImpl();
        return y;
    }
}
