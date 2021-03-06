#include "Texture.h"
#include "stb_image/stb_image.h"

Texture::Texture(std::string filePath)
	:m_RendererID(0), m_FilePath(filePath), m_LocalBufer(0), m_Height(0), m_Width(0), m_BPP(0)
{
	stbi_set_flip_vertically_on_load(1);
	m_LocalBufer = stbi_load(m_FilePath.c_str(), &m_Width, &m_Height, &m_BPP, 4); // 4 = RGBA

	GLCall(glGenTextures(1, &m_RendererID));
	Bind();

	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));			// GL_LINEAR_MIPMAP_LINERA is not working on static objects
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));		// Prevent from stretching the texture
	GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

	GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBufer));
	//GLCall(glGenerateMipmap(GL_TEXTURE_2D));
	Unbind();

	if (m_LocalBufer)
		stbi_image_free(m_LocalBufer);
}

Texture::~Texture()
{
	GLCall(glDeleteTextures(1, &m_RendererID));
}

void Texture::Bind(unsigned int slot) const
{
	GLCall(glActiveTexture(GL_TEXTURE0 + slot));
	GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));
}

void Texture::BindTextureUV(const void* textureUV, unsigned int size) 
{
	//glTexCoordPointer(2, GL_FLOAT, 0, textureUV);

	GLCall(glGenBuffers(1, &m_RendererID));
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
	GLCall(glBufferData(GL_ARRAY_BUFFER, size, textureUV, GL_STATIC_DRAW));
}

void Texture::Unbind() const
{
	GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));
}
