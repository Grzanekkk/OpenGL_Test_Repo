#pragma once

#include "Test.h"
#include "Texture.h"
#include "VertexBufferLayout.h"
#include "Renderer.h"

namespace test
{
	class TestTexture : public Test
	{
	public:
		TestTexture();
		~TestTexture();

		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnImGuiRender() override;
	private:
		void SetUpRendering();

	private:
		Texture texture = Texture("res/textures/papaj.png");
		VertexArray m_VertexArray;
		IndexBuffer m_IndexBuffer;
		Shader m_Shader;

		glm::vec3 m_TranslationA, m_TranslationB;
	};
}
