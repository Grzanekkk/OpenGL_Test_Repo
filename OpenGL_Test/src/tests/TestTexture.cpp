#include "TestTexture.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "imgui/imgui.h"

namespace test
{
	TestTexture::TestTexture()
		: m_TranslationA(200, 200, 0), m_TranslationB(400, 300, 0), m_Shader("res/shaders/Basic.shader")
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
		Renderer renderer;

		renderer.Draw(m_VertexArray, m_IndexBuffer, m_Shader);

		GLCall(glClearColor(0.1f, 0.3f, 0.8f, 1.0f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));

		{
			glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationA);
			glm::mat4 mvp = projection * view * model;
			m_Shader.SetUniformMat4f("u_MVP", mvp);
			renderer.Draw(m_VertexArray, m_IndexBuffer, m_Shader);
		}

		{
			glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationB);
			glm::mat4 mvp = projection * view * model;
			m_Shader.SetUniformMat4f("u_MVP", mvp);
			renderer.Draw(m_VertexArray, m_IndexBuffer, m_Shader);
		}

	}

	void TestTexture::OnImGuiRender()
	{
		ImGui::SliderFloat3("Translation A", &m_TranslationA.x, 0.0f, 960.0f);
		ImGui::SliderFloat3("Translation B", &m_TranslationB.x, 0.0f, 960.0f);
		ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
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

		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));		// Allows transparency

		VertexBuffer vb(positions, 4 * 4 * sizeof(float));

		VertexBufferLayout layout;
		layout.Push<float>(2);  
		layout.Push<float>(2);  
		m_VertexArray.AddBuffer(vb, layout);

		m_IndexBuffer = IndexBuffer(indices, 6);

		glm::mat4 projection = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f);   // Converts 3D world coordinates to screen space coordinates between -1 and 1
		glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));


		m_Shader.Bind();
		m_Shader.SetUniform4f("u_Color", 0.8f, 0.5f, 0.8f, 1.0f);

		texture.Bind();
		m_Shader.SetUniform1i("u_Texture", 0);
	}
}