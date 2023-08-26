#pragma once
#include <Bento.h>

#include "ParticleSystem.h"

class Sandbox2D : public Bento::Layer
{

public:
	Sandbox2D();
	virtual ~Sandbox2D() = default;
	virtual void OnAttach() override;
	virtual void OnDeAttach() override;
	virtual void OnUpdate(Bento::Timestep ts) override;
	virtual void OnImGuiRender() override;
	virtual void OnEvent(Bento::Event& event) override;

private:
	Bento::OrthographicCameraController m_CameraController;

	Bento::Ref<Bento::Texture2D> m_Texture;
	Bento::Ref<Bento::Texture2D> m_SpriteSheet;
	Bento::Ref<Bento::SubTexture2D> m_ErrorTexture;

	glm::vec4 m_SquareColor = glm::vec4(0.3f, 0.3f, 0.8f, 1.0f);

	ParticleProps m_Particle;
	ParticleSystem m_ParticleSystem;

	std::unordered_map<char, Bento::Ref<Bento::SubTexture2D>> s_TextureMap;
};

