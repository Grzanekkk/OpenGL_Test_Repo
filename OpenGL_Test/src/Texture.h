#pragma once

#include "Renderer.h"

class Texture
{
private:
	unsigned int m_RendererID;
	std::string m_FilePath;
	unsigned char* m_LocalBufer;
	int m_Width, m_Height, m_BPP;	// BPP == Bits Per Pixel
public:
	Texture(std::string filePath);
	~Texture();

	void BindTextureUV(const void* textureUV, unsigned int size);
	void Bind(unsigned int slot = 0) const;
	void Unbind() const;
};