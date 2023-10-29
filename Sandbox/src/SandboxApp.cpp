#include "Blaze.h"

#include "Blaze/Core/EntryPoint.h"

#include "Sandbox2D.h"

class Sandbox : public Blaze::Application
{
public:
    Sandbox()
    {
        PushLayer(new Sandbox2D());
    }

    ~Sandbox() override
    {
    }
};

Blaze::Application* Blaze::CreateApplication()
{
    return new Sandbox();
}