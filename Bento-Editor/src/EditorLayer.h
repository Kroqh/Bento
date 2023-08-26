#pragma once
#include <Bento.h>

namespace Bento {

	class EditorLayer : public Bento::Layer
	{

	public:
		EditorLayer();
		virtual ~EditorLayer() = default;
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
		Bento::Ref<Bento::Framebuffer> m_Framebuffer;

		glm::vec4 m_SquareColor = glm::vec4(0.3f, 0.3f, 0.8f, 1.0f);

		glm::vec2 m_ViewportSize = {0.0f, 0.0f};

		std::unordered_map<char, Bento::Ref<Bento::SubTexture2D>> s_TextureMap;
	};

}



