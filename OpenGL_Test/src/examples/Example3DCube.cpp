#include "Example3DCube.h"

#include "VertexBufferLayout.h"
#include "Renderer.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"


example::Example3DCube::Example3DCube()
	: m_ClearColor{0.44f, 1.0f, 0.94f, 1.0f}
{
	float vertices[] = {
		-1.0f, -1.0f,  1.0f,
		 1.0f, -1.0f,  1.0f,
		 1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,	// front face

		-1.0f, -1.0f, -1.0f,
		 1.0f, -1.0f, -1.0f,
		 1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f		// back face
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

	m_VertexBuffer = std::make_unique<VertexBuffer>(vertices, 3 * 8 * sizeof(float));

	VertexBufferLayout layout;
	layout.Push<float>(3);

	m_VertexArray = std::make_unique<VertexArray>();
	m_VertexArray->AddBuffer(*m_VertexBuffer, layout);

	m_IndexBuffer = std::make_unique<IndexBuffer>(indices, 2 * 3 * 6);

	m_Shader = std::make_unique<Shader>("res/shaders/Basic.shader");
	m_Shader->Bind();
	m_Shader->SetUniform4f("u_Color", 0.2f, 0.5f, 0.5f, 1.0f);
	m_Shader->SetUniform4f("u_Color", 0.2f, 0.5f, 0.5f, 1.0f);

	m_Texture = std::make_unique<Texture>("res/textures/papaj.png");
	m_Shader->SetUniform1i("u_Texture", 0);
}

example::Example3DCube::~Example3DCube()
{

}

void example::Example3DCube::OnUpdate(float deltaTime)
{

}

void example::Example3DCube::OnRender()
{
	Renderer renderer;

	GLCall(glClearColor(m_ClearColor[0], m_ClearColor[1], m_ClearColor[2], m_ClearColor[3]));
	GLCall(glEnable(GL_DEPTH_TEST));
	GLCall(glDepthFunc(GL_LESS));

	glm::mat4 model = glm::mat4(1.0f);
	//model = glm::rotate(model, 30.0f, glm::vec3(1.0f, 0.0f, 0.0f));
	glm::mat4 view = glm::lookAt(
		glm::vec3(4, 3, 3), // Camera is at (4,3,3), in World Space
		glm::vec3(0, 0, 0), // and looks at the origin.
		glm::vec3(0, 1, 0)
	);
	glm::mat4 projection = glm::perspective(45.0f, 16.0f / 9.0f, 0.1f, 100.0f);

	glm::mat4 MVP = projection * view * model;
	m_Shader->Bind();
	m_Shader->SetUniformMat4f("u_MVP", MVP);

	renderer.Draw(*m_VertexArray, *m_IndexBuffer, *m_Shader);

	GLCall(glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT));
}

void example::Example3DCube::OnImGuiRender()
{

}
