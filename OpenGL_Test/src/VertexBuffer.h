#pragma once

class VertexBuffer
{
private:
	unsigned int m_RendererID;
public:
	VertexBuffer(const void* data, unsigned int size);
	VertexBuffer(float vertexData[], float textureCoordData[], unsigned int size);
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;
	void* CombineVertexWithTextureCoord(float vertexData[], float textureCoordData[]) const;

	unsigned int m_Size;
};

