#pragma once

#include "Blaze/Input/Input.h"

namespace Blaze
{
    class WindowsInput : public Input
    {
    protected:
        virtual bool IsKeyPressedImpl(const int keycode) override;
        virtual bool IsMouseButtonPressedImpl(const int button) override;

        virtual std::pair<float, float> GetMousePosImpl() override;
        virtual float GetMouseXImpl() override;
        virtual float GetMouseYImpl() override;
    };
}
