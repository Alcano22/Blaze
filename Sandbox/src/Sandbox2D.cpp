#include "Sandbox2D.h"

#include "Platform/OpenGL/OpenGLShader.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <imgui/imgui.h>

Sandbox2D::Sandbox2D()
	: Layer("Sandbox2D"), m_CameraController(1280.0f / 720.0f, true)
{
}

void Sandbox2D::OnAttach()
{
    m_SquareVA = Blaze::VertexArray::Create();

    constexpr float squareVertices[3 * 4] = {
        // Position
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.5f,  0.5f, 0.0f,
        -0.5f,  0.5f, 0.0f
    };
    
    Blaze::Ref<Blaze::VertexBuffer> squareVB;
    squareVB.reset(Blaze::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
    squareVB->SetLayout({
        { Blaze::ShaderDataType::Float3, "a_Position" }
    });
    m_SquareVA->AddVertexBuffer(squareVB);
    
    const uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
    Blaze::Ref<Blaze::IndexBuffer> squareIB;
    squareIB.reset(Blaze::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
    m_SquareVA->SetIndexBuffer(squareIB);
    
    m_FlatColorShader = Blaze::Shader::Create("assets/shaders/flat_color.glsl");
}

void Sandbox2D::OnDetach()
{
	
}

void Sandbox2D::OnUpdate(const Blaze::Timestep ts)
{
	m_CameraController.OnUpdate(ts);

	Blaze::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
	Blaze::RenderCommand::Clear();
        
	Blaze::Renderer::BeginScene(m_CameraController.GetCamera());

	std::dynamic_pointer_cast<Blaze::OpenGLShader>(m_FlatColorShader)->Bind();
	std::dynamic_pointer_cast<Blaze::OpenGLShader>(m_FlatColorShader)->UploadUniformFloat4("u_Color", m_SquareColor);

	Blaze::Renderer::Submit(m_FlatColorShader, m_SquareVA, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
        
	Blaze::Renderer::EndScene();
}

void Sandbox2D::OnImGuiRender()
{
	ImGui::Begin("Settings");
	ImGui::ColorEdit4("Square Color", glm::value_ptr(m_SquareColor));
	ImGui::End();
}

void Sandbox2D::OnEvent(Blaze::Event& event)
{
	m_CameraController.OnEvent(event);
}
