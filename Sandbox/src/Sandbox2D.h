#pragma once

#include "Blaze.h"

class Sandbox2D : public Blaze::Layer
{
public:
	explicit Sandbox2D();
	virtual ~Sandbox2D() = default;
	
	virtual void OnAttach() override;
	virtual void OnDetach() override;

	virtual void OnUpdate(const Blaze::Timestep ts) override;

	virtual void OnImGuiRender() override;

	virtual void OnEvent(Blaze::Event& event) override;
private:
	Blaze::OrthographicCameraController m_CameraController;

	// Temp
	Blaze::Ref<Blaze::VertexArray> m_SquareVA;
	Blaze::Ref<Blaze::Shader> m_Shader;
	Blaze::Ref<Blaze::Shader> m_FlatColorShader;

	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.0f };
};
