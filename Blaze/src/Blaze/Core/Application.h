#pragma once

#include "Core.h"
#include "Window.h"
#include "LayerStack.h"
#include "Blaze/Event/ApplicationEvent.h"

#include "Blaze/ImGui/ImGuiLayer.h"

namespace Blaze
{
    class Application
    {
    public:
        Application();
        virtual ~Application();

        void Run();
        
        void OnEvent(Event& event);

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* overlay);

        static Application& Get() { return *s_Instance; }
        Window& GetWindow() const { return *m_Window; }
    private:
        bool OnWindowClose(WindowCloseEvent& event);
    private:
        static Application* s_Instance;
        
        std::unique_ptr<Window> m_Window;
        ImGuiLayer* m_ImGuiLayer;
        bool m_Running = true;
        LayerStack m_LayerStack;

        uint32_t m_VertexArray, m_VertexBuffer, m_IndexBuffer;
    };

    Application* CreateApplication();
}
