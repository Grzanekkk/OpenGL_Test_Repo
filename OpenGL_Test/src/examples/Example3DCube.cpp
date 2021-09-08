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

	m_IndexBuffer = std::make_unique<IndexBuffer>(indices, 24);

	m_Shader = std::make_unique<Shader>("res/shaders/Basic.Shader");
	m_Shader->Bind();

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
	GLCall(glClear(GL_COLOR_BUFFER_BIT));

	glm::mat4 model;
	glm::mat4 view;
	glm::mat4 projection;

	glm::mat4 MVP = model * view * projection;

}

void example::Example3DCube::OnImGuiRender()
{

}
