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
		/*Texture texture = Texture("res/textures/papaj.png");
		VertexArray va;
		Renderer renderer;
		IndexBuffer ib;
		Shader shader;*/
	};
}
