#include "VertexBuffer.h"

#include "Renderer.h"

VertexBuffer::VertexBuffer(const void* data, unsigned int size)     // Data == positions, rotations etc. of Vertex
	: m_Size(size)
{
	GLCall(glGenBuffers(1, &m_RendererID));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
	GLCall(glBufferData(GL_ARRAY_BUFFER, m_Size, data, GL_STATIC_DRAW));
}

VertexBuffer::VertexBuffer(float vertexData[], float textureCoordData[], unsigned int size)     // Data == positions, rotations etc. of Vertex
	: m_Size(size)
{
	std::vector<float>m_VertexData(vertexData, vertexData + sizeof(vertexData) / sizeof(vertexData[0]));
	std::vector<float> m_TextureCoordData(textureCoordData, textureCoordData + sizeof(textureCoordData) / sizeof(textureCoordData[0]));
	const void* data = CombineVertexWithTextureCoord(vertexData, textureCoordData);
	GLCall(glGenBuffers(1, &m_RendererID));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
	GLCall(glBufferData(GL_ARRAY_BUFFER, m_Size, data, GL_STATIC_DRAW));
}

VertexBuffer::~VertexBuffer()
{
    GLCall(glDeleteBuffers(1, &m_RendererID));
}

void VertexBuffer::Bind() const
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
}

void VertexBuffer::Unbind() const
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

void* VertexBuffer::CombineVertexWithTextureCoord(float vertexData[], float textureCoordData[]) const
{
	std::vector<float> data;
	int vertexID = 0;
	int textureID = 0 ;

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			data.push_back(vertexData[vertexID]);
			vertexID++;
		}
		for (int k = 0; k < 4; k++)
		{
			data.push_back(textureCoordData[textureID]);
			textureID++;
		}
	}


	void* ptr = std::data(data);
	return ptr;
}
