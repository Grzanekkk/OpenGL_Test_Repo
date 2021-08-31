#include "TestTexture.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace test
{
	TestTexture::TestTexture()
	{
		SetUpRendering();
	}

	TestTexture::~TestTexture()
	{

	}

	void TestTexture::OnUpdate(float deltaTime)
	{

	}

	void TestTexture::OnRender()
	{
		renderer.Draw(va, ib, shader);
	}

	void TestTexture::OnImGuiRender()
	{

	}

	void TestTexture::SetUpRendering()
	{
		float positions[] = {
			-50.0f, -50.0f, 0.0f, 0.0f, // 0
			 50.0f, -50.0f, 1.0f, 0.0f, // 1
			 50.0f,  50.0f, 1.0f, 1.0f, // 2
			-50.0f,  50.0f, 0.0f, 1.0f  // 3
		};

		unsigned int indices[] = {
			0, 1, 2,
			2, 3, 0
		};

		va;
		VertexBuffer vb(positions, 4 * 4 * sizeof(float));

		VertexBufferLayout layout;
		layout.Push<float>(2);  
		layout.Push<float>(2);  
		va.AddBuffer(vb, layout);

		ib = IndexBuffer(indices, 6);

		glm::mat4 projection = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f);   // Converts 3D world coordinates to screen space coordinates between -1 and 1
		glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));

		shader = Shader("res/shaders/Basic.shader");
		shader.Bind();
		shader.SetUniform4f("u_Color", 0.8f, 0.5f, 0.8f, 1.0f);

		texture.Bind();
		shader.SetUniform1i("u_Texture", 0);
	}
}