#pragma once

#include "Test.h"
#include "Texture.h"
#include "VertexBufferLayout.h"
#include "Renderer.h"

#include <memory>

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
		std::unique_ptr<Texture> m_Texture;
		std::unique_ptr<VertexArray> m_VertexArray;
		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;
		std::unique_ptr<Shader> m_Shader;

		glm::vec3 m_TranslationA, m_TranslationB;
	};
}
