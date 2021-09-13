#include "Example3DCube.h"

#include "VertexBufferLayout.h"
#include "Renderer.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "imgui/imgui.h"

#include <GLFW/glfw3.h>

namespace example
{

	Example3DCube::Example3DCube()
		: m_ClearColor{ 0.44f, 1.0f, 0.94f, 1.0f }, m_CameraTranslation(0, 0, -5), m_CameraRotation(0, 0, 0)
	{
		float vertices[] = {
			-1.0f, -1.0f,  1.0f, 0.0f, 0.0f,
			 1.0f, -1.0f,  1.0f, 1.0f, 0.0f,
			 1.0f,  1.0f,  1.0f, 1.0f, 1.0f,
			-1.0f,  1.0f,  1.0f, 0.0f, 1.0f,	// front face

			-1.0f, -1.0f, -1.0f, 0.0f, 0.0f,
			 1.0f, -1.0f, -1.0f, 1.0f, 0.0f,
			 1.0f,  1.0f, -1.0f, 1.0f, 1.0f,
			-1.0f,  1.0f, -1.0f, 0.0f, 1.0f,	// back face
		};

		unsigned int indices[] = {
			0, 1, 2,	// One triangle
			2, 3, 0,

			1, 5, 6,	// One Face
			6, 2, 1,	// One Face

			5, 4, 7,
			7, 6, 5,

			4, 0, 3,
			3, 7, 4,

			0, 1, 5,
			5, 4, 0,

			3, 2, 6,
			6, 7, 3
		};

		float textureUV[] = {
		0.000059f, 1.0f - 0.000004f,
	0.000103f, 1.0f - 0.336048f,
	0.335973f, 1.0f - 0.335903f,
	1.000023f, 1.0f - 0.000013f,
	0.667979f, 1.0f - 0.335851f,
	0.999958f, 1.0f - 0.336064f,
	0.667979f, 1.0f - 0.335851f,
	0.336024f, 1.0f - 0.671877f,
	0.667969f, 1.0f - 0.671889f,
	1.000023f, 1.0f - 0.000013f,
	0.668104f, 1.0f - 0.000013f,
	0.667979f, 1.0f - 0.335851f,
	0.000059f, 1.0f - 0.000004f,
	0.335973f, 1.0f - 0.335903f,
	0.336098f, 1.0f - 0.000071f,
	0.667979f, 1.0f - 0.335851f,
	0.335973f, 1.0f - 0.335903f,
	0.336024f, 1.0f - 0.671877f,
	1.000004f, 1.0f - 0.671847f,
	0.999958f, 1.0f - 0.336064f,
	0.667979f, 1.0f - 0.335851f,
	0.668104f, 1.0f - 0.000013f,
	0.335973f, 1.0f - 0.335903f,
	0.667979f, 1.0f - 0.335851f,
	0.335973f, 1.0f - 0.335903f,
	0.668104f, 1.0f - 0.000013f,
	0.336098f, 1.0f - 0.000071f,
	0.000103f, 1.0f - 0.336048f,
	0.000004f, 1.0f - 0.671870f,
	0.336024f, 1.0f - 0.671877f,
	0.000103f, 1.0f - 0.336048f,
	0.336024f, 1.0f - 0.671877f,
	0.335973f, 1.0f - 0.335903f,
	0.667969f, 1.0f - 0.671889f,
	1.000004f, 1.0f - 0.671847f,
	0.667979f, 1.0f - 0.335851f
		};
		

		GLCall(glEnable(GL_BLEND));
		GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

		m_VertexBuffer = std::make_unique<VertexBuffer>(vertices, 5 * 8 * sizeof(float));

		VertexBufferLayout layout;
		layout.Push<float>(3);
		layout.Push<float>(2);

		m_Texture = std::make_unique<Texture>("res/textures/spongebob.png");
		m_Texture->BindTextureUV(textureUV, 34 * sizeof(float));

		m_VertexArray = std::make_unique<VertexArray>();
		m_VertexArray->AddBuffer(*m_VertexBuffer, layout);

		m_IndexBuffer = std::make_unique<IndexBuffer>(indices, 2 * 3 * 6);

		m_Shader = std::make_unique<Shader>("res/shaders/Basic.shader");
		m_Shader->Bind();
		//m_Shader->SetUniform4f("u_Color", 0.2f, 0.5f, 0.5f, 1.0f);

		m_Shader->SetUniform1i("u_Texture", 0);
	}

	Example3DCube::~Example3DCube()
	{

	}

	void Example3DCube::OnUpdate(float deltaTime)
	{

	}

	void Example3DCube::OnRender()
	{
		Renderer renderer;

		GLCall(glClearColor(m_ClearColor[0], m_ClearColor[1], m_ClearColor[2], m_ClearColor[3]));
		GLCall(glEnable(GL_DEPTH_TEST));
		GLCall(glDepthFunc(GL_LESS));

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::rotate(model, glm::radians(-20.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		glm::mat4 projection = glm::perspective(glm::radians(45.0f), 960.0f / 540.0f, 0.1f, 300.0f);
		//glm::mat4 view = glm::lookAt(
		//	m_CameraTranslation, // Camera is at (4,3,3), in World Space
		//	m_CameraRotation, // and looks at the origin.
		//	glm::vec3(0, 1, 0)
		//);

		const float radius = 10.0f;
		float camX = sin(glfwGetTime()) * -radius;
		float camZ = cos(glfwGetTime()) * radius;

		glm::mat4 view = glm::lookAt(
			glm::vec3(camX, 3.0f, camZ),
			glm::vec3(0.0f, 0.0f, 0.0f),
			glm::vec3(0.0f, 1.0f, 0.0f)
		);

		//glm::mat4 view = glm::mat4(1.0f);
		//view = glm::translate(view, glm::vec3(0.0f, 0.0f, -5.0f));

		glm::mat4 MVP = projection * view * model;
		m_Shader->Bind();
		m_Shader->SetUniformMat4f("u_MVP", MVP);

		GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));

		renderer.Draw(*m_VertexArray, *m_IndexBuffer, *m_Shader);

	}

	void Example3DCube::OnImGuiRender()
	{
		ImGui::SliderFloat3("Camera Location", &m_CameraTranslation.x, -200.0f, 200.0f);
		ImGui::SliderFloat3("Camera Point To Look To", &m_CameraRotation.x, -180.0f, 180.0f);
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	}
}
