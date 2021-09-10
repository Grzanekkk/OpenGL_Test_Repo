#include "ExampleTexture2D.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "imgui/imgui.h"

namespace example
{
	ExampleTexture2D::ExampleTexture2D()
		: m_TranslationA(0, 0, 24), m_TranslationB(400, 300, 10), m_CameraTranslation(0, 0, -20), m_CameraRotation(0, 0, 0)
	{
		SetUpRendering();
	}

	ExampleTexture2D::~ExampleTexture2D()
	{
		// Smart pointers will handle memory 
	}

	void ExampleTexture2D::OnUpdate(float deltaTime)
	{

	}

	void ExampleTexture2D::OnRender()
	{
		Renderer renderer;
		
		GLCall(glClearColor(0.1f, 0.3f, 0.8f, 1.0f));
		GLCall(glClear(GL_COLOR_BUFFER_BIT));

		//glm::mat4 projection = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -200.0f, 200.0f);   // Converts 3D world coordinates to screen space coordinates between -1 and 1
		//glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));

		glm::mat4 projection = glm::perspective(90.0f, 16.0f / 9.0f, 0.1f, 300.0f);
		glm::mat4 view = glm::lookAt(
			m_CameraTranslation, // Camera is at (4,3,3), in World Space
			m_CameraRotation, // and looks at the origin.
			glm::vec3(0, 1, 0)
		);

		m_Texture->Bind();

		{	// Rendering First Object
			glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationA);
			glm::mat4 mvp = projection * view * model;
			m_Shader->Bind();
			m_Shader->SetUniformMat4f("u_MVP", mvp);
			renderer.Draw(*m_VertexArray, *m_IndexBuffer, *m_Shader);
		}

		{	//Rendering Second Object
			glm::mat4 model = glm::translate(glm::mat4(1.0f), m_TranslationB);
			glm::mat4 mvp = projection * view * model;
			m_Shader->Bind();
			m_Shader->SetUniformMat4f("u_MVP", mvp);
			renderer.Draw(*m_VertexArray, *m_IndexBuffer, *m_Shader);
		}
	}

	void ExampleTexture2D::OnImGuiRender()
	{
		ImGui::SliderFloat3("Translation A", &m_TranslationA.x, 0.0f, 960.0f);
		ImGui::SliderFloat3("Translation B", &m_TranslationB.x, 0.0f, 960.0f);
		ImGui::SliderFloat3("Camera Location", &m_CameraTranslation.x, -180.0f, 180.0f);
		ImGui::SliderFloat3("Camera Point To Look To", &m_CameraRotation.x, -180.0f, 180.0f);
		ImGui::Text("This is some useful text.");
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	}

	void ExampleTexture2D::SetUpRendering()
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

		m_VertexBuffer = std::make_unique<VertexBuffer>(positions, 4 * 4 * sizeof(float));
		VertexBufferLayout layout;
		layout.Push<float>(2);  
		layout.Push<float>(2);  

		m_VertexArray = std::make_unique<VertexArray>();
		m_VertexArray->AddBuffer(*m_VertexBuffer, layout);

		m_IndexBuffer = std::make_unique<IndexBuffer>(indices, 2 * 3);
		m_Texture = std::make_unique<Texture>("res/textures/papaj.png");
		
		m_Shader = std::make_unique<Shader>("res/shaders/Basic.shader");
		m_Shader->Bind();
		m_Shader->SetUniform4f("u_Color", 0.8f, 0.5f, 0.8f, 1.0f);
		m_Shader->SetUniform1i("u_Texture", 0);
	}
}