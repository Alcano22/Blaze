#include "Blaze.h"

#include "Blaze/Event/KeyEvent.h"

#include <glm/glm.hpp>

#include "imgui/imgui.h"

class ExampleLayer : public Blaze::Layer
{
public:
    ExampleLayer()
        : Layer("Example")
    {
    }

    void OnUpdate() override
    {
        // BLZ_INFO("ExampleLayer::Update");

        if (Blaze::Input::IsKeyPressed(BLZ_KEY_TAB))
            BLZ_INFO("Tab key is pressed!");
    }

    void OnImGuiRender() override
    {
        ImGui::Begin("Test");
        ImGui::Text("Hello World!");
        ImGui::End();
    }

    void OnEvent(Blaze::Event& event) override
    {
        // BLZ_TRACE("{0}", event.ToString());

        if (event.GetEventType() != Blaze::EventType::KeyPressed) return;

        const Blaze::KeyPressedEvent& keyPressedEvent = (Blaze::KeyPressedEvent&)event;
        if (keyPressedEvent.GetKeyCode() != BLZ_KEY_TAB) return;

        constexpr glm::vec4 a(1.0f, 2.0f, 3.0f, 4.0f);
        constexpr glm::vec4 b(4.0f, 3.0f, 2.0f, 1.0f);

        BLZ_INFO("{0}, {1}, {2}, {3}", a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w);
    }
};

class Sandbox : public Blaze::Application
{
public:
    Sandbox()
    {
        PushLayer(new ExampleLayer());
    }

    ~Sandbox() override
    {
    }
};

Blaze::Application* Blaze::CreateApplication()
{
    return new Sandbox();
}