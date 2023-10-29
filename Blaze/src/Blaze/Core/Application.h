#pragma once

#include "Core.h"
#include "Window.h"
#include "LayerStack.h"
#include "Blaze/Event/ApplicationEvent.h"

#include "Blaze/Core/Timestep.h"

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
        bool OnWindowClose(const WindowCloseEvent& event);
        bool OnWindowResize(const WindowResizeEvent& event);
    private:
        Scope<Window> m_Window;
        ImGuiLayer* m_ImGuiLayer;
        bool m_Running = true;
        bool m_Minimized = false;
        LayerStack m_LayerStack;
        float m_LastFrameTime = 0.0f;
    private:
        static Application* s_Instance;
    };

    Application* CreateApplication();
}
