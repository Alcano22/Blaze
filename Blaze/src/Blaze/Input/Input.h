#pragma once

#include "Blaze/Core/Core.h"

namespace Blaze
{
    class Input
    {
    public:
        static bool IsKeyPressed(const int keycode) { return s_Instance->IsKeyPressedImpl(keycode); }
        static bool IsMouseButtonPressed(const int button) { return s_Instance->IsMouseButtonPressedImpl(button); }

        static std::pair<float, float> GetMousePos() { return s_Instance->GetMousePosImpl(); } 
        static float GetMouseX() { return s_Instance->GetMouseXImpl(); }
        static float GetMouseY() { return s_Instance->GetMouseYImpl(); }

    protected:
        virtual bool IsKeyPressedImpl(const int keycode) = 0;
        virtual bool IsMouseButtonPressedImpl(const int button) = 0;

        virtual std::pair<float, float> GetMousePosImpl() = 0;
        virtual float GetMouseXImpl() = 0;
        virtual float GetMouseYImpl() = 0;
    private:
        static Input* s_Instance;
    };
}