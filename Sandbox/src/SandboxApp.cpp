#include <iostream>

#include "Blaze.h"

#include "Blaze/Event/KeyEvent.h"

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

#include <imgui/imgui.h>

class ExampleLayer : public Blaze::Layer
{
public:
    ExampleLayer()
        : Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f),
          m_CameraPosition(0.0f, 0.0f, 0.0f), m_SquarePosition(0.0f, 0.0f, 0.0f)
    {
        m_VertexArray.reset(Blaze::VertexArray::Create());

        constexpr float vertices[3 * 7] = {
            // Position             // Color
            -0.5f, -0.5f, 0.0f,     0.8f, 0.2f, 0.8f, 1.0f,
             0.5f, -0.5f, 0.0f,     0.2f, 0.3f, 0.8f, 1.0f,
             0.0f,  0.5f, 0.0f,     0.8f, 0.8f, 0.2f, 1.0f
        };

        m_VertexBuffer.reset(Blaze::VertexBuffer::Create(vertices, sizeof(vertices)));
        const Blaze::BufferLayout layout = {
            { Blaze::ShaderDataType::Float3, "a_Position" },
            { Blaze::ShaderDataType::Float4, "a_Color" }
        };
        m_VertexBuffer->SetLayout(layout);
        m_VertexArray->AddVertexBuffer(m_VertexBuffer);

        constexpr uint32_t indices[3] = { 0, 1, 2 };
        m_IndexBuffer.reset(Blaze::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
        m_VertexArray->SetIndexBuffer(m_IndexBuffer);
        
        m_SquareVA.reset(Blaze::VertexArray::Create());

        constexpr float squareVertices[3 * 4] = {
            // Position
            -0.5f, -0.5f, 0.0f,
             0.5f, -0.5f, 0.0f,
             0.5f,  0.5f, 0.0f,
            -0.5f,  0.5f, 0.0f
        };
        
        std::shared_ptr<Blaze::VertexBuffer> squareVB;
        squareVB.reset(Blaze::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
        squareVB->SetLayout({
            { Blaze::ShaderDataType::Float3, "a_Position" }
        });
        m_SquareVA->AddVertexBuffer(squareVB);
        
        const uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
        std::shared_ptr<Blaze::IndexBuffer> squareIB;
        squareIB.reset(Blaze::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
        m_SquareVA->SetIndexBuffer(squareIB);

        const std::string vertexSrc = R"(
            #version 330 core
            
            layout(location = 0) in vec3 a_Position;
            layout(location = 1) in vec4 a_Color;

            uniform mat4 u_ViewProjection;
            uniform mat4 u_Transform;

            out vec4 v_Color;

            void main()
            {
                v_Color = a_Color;
                gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0f);
            }
        )";

        const std::string fragmentSrc = R"(
            #version 330 core

            layout(location = 0) out vec4 color;

            in vec4 v_Color;

            void main()
            {
                color = v_Color;
            }
        )";
        
        m_Shader.reset(new Blaze::Shader(vertexSrc, fragmentSrc));

        const std::string flatColorShaderVertexSrc = R"(
            #version 330 core
            
            layout(location = 0) in vec3 a_Position;
            layout(location = 1) in vec4 a_Color;

            uniform mat4 u_ViewProjection;
            uniform mat4 u_Transform;

            out vec4 v_Color;

            void main()
            {
                v_Color = a_Color;
                gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0f);
            }
        )";

        const std::string flatColorShaderFragmentSrc = R"(
            #version 330 core

            layout(location = 0) out vec4 color;

            uniform vec4 u_Color;

            void main()
            {
                color = u_Color;
            }
        )";

        m_FlatColorShader.reset(new Blaze::Shader(flatColorShaderVertexSrc, flatColorShaderFragmentSrc));
    }

    void OnUpdate(const Blaze::Timestep ts) override
    {
        BLZ_TRACE("Delta Time: {0}s ({1}ms)", ts.GetSeconds(), ts.GetMilliseconds());
        
        if (Blaze::Input::IsKeyPressed(BLZ_KEY_A))
            m_CameraPosition.x -= m_CameraMoveSpeed * ts;
        if (Blaze::Input::IsKeyPressed(BLZ_KEY_D))
            m_CameraPosition.x += m_CameraMoveSpeed * ts;
        if (Blaze::Input::IsKeyPressed(BLZ_KEY_S))
            m_CameraPosition.y -= m_CameraMoveSpeed * ts;
        if (Blaze::Input::IsKeyPressed(BLZ_KEY_W))
            m_CameraPosition.y += m_CameraMoveSpeed * ts;
        if (Blaze::Input::IsKeyPressed(BLZ_KEY_Q))
            m_CameraRotation += m_CameraRotateSpeed * ts;
        if (Blaze::Input::IsKeyPressed(BLZ_KEY_E))
            m_CameraRotation -= m_CameraRotateSpeed * ts;

        if (Blaze::Input::IsKeyPressed(BLZ_KEY_LEFT))
            m_SquarePosition.x -= m_SquareMoveSpeed * ts;
        if (Blaze::Input::IsKeyPressed(BLZ_KEY_RIGHT))
            m_SquarePosition.x += m_SquareMoveSpeed * ts;
        if (Blaze::Input::IsKeyPressed(BLZ_KEY_DOWN))
            m_SquarePosition.y -= m_SquareMoveSpeed * ts;
        if (Blaze::Input::IsKeyPressed(BLZ_KEY_UP))
            m_SquarePosition.y += m_SquareMoveSpeed * ts;

        Blaze::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
        Blaze::RenderCommand::Clear();
            
        m_Camera.SetPosition(m_CameraPosition);
        m_Camera.SetRotation(m_CameraRotation);
            
        Blaze::Renderer::BeginScene(m_Camera);

        const glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

        constexpr glm::vec4 redColor(0.8f, 0.2f, 0.3f, 1.0f);
        constexpr glm::vec4 blueColor(0.2f, 0.3f, 0.8f, 1.0f);
        for (int y = 0; y < 20; y++)
        {
            for (int x = 0; x < 20; x++)
            {
                const int index = x + y;
                if (index % 2 == 0)
                    m_FlatColorShader->UploadUniformFloat4("u_Color", redColor);
                else
                    m_FlatColorShader->UploadUniformFloat4("u_Color", blueColor);
                
                glm::vec3 pos = glm::vec3(x * 0.11f, y * 0.11f, 0.0f) + m_SquarePosition;
                const glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
                Blaze::Renderer::Submit(m_FlatColorShader, m_SquareVA, transform);
            }
        }
        
        Blaze::Renderer::Submit(m_Shader, m_VertexArray);
            
        Blaze::Renderer::EndScene();
    }

    void OnImGuiRender() override
    {
    }

    void OnEvent(Blaze::Event& event) override
    {
    }
private:
    std::shared_ptr<Blaze::Shader> m_Shader;
    std::shared_ptr<Blaze::VertexArray> m_VertexArray;
    std::shared_ptr<Blaze::VertexBuffer> m_VertexBuffer;
    std::shared_ptr<Blaze::IndexBuffer> m_IndexBuffer;

    std::shared_ptr<Blaze::Shader> m_FlatColorShader;
    std::shared_ptr<Blaze::VertexArray> m_SquareVA;

    Blaze::OrthographicCamera m_Camera;
    glm::vec3 m_CameraPosition;
    float m_CameraRotation = 0.0f;
    float m_CameraMoveSpeed = 2.0f;
    float m_CameraRotateSpeed = 30.0f;

    glm::vec3 m_SquarePosition;
    float m_SquareMoveSpeed = 1.0f;
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