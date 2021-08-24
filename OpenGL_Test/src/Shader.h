#pragma once


#include <string>
#include <unordered_map>

struct ShaderProgramSource
{
	std::string VertexSourde;
	std::string FragmentSourde;
};

class Shader
{
private:
	std::string m_FilePath;
	unsigned int m_RendererID;
	std::unordered_map<std::string, int> m_UniformLocationCache;
public:
	Shader(const std::string& filepath);
	~Shader();

	void Bind() const;
	void Unbind() const;

	void SetUniform1i(const std::string& name, int value);
	void SetUniform1f(const std::string& name, float v1);
	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);

private:
	bool CompileShader();
	ShaderProgramSource ParseShaderSourceCode(const std::string& filepath);
	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
	unsigned int CompileShader(unsigned int type, const std::string& source);

	int GetUniformLocation(const std::string& name);
};
