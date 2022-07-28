#include "material.h"
#include "glad/glad.h"

namespace ROGLL
{
	Material::Material(const Shader& shader)
		: m_shader(shader)
	{}

	void Material::Set4(const std::string& name, Vector4<int> value)
	{
		int location = m_shader.GetUniformLocation(name);
		glUniform4i(location, value.x, value.y, value.z, value.w);
	}

	void Material::Set4(const std::string& name, Vector4<unsigned int> value)
	{
		int location = m_shader.GetUniformLocation(name);
		glUniform4ui(location, value.x, value.y, value.z, value.w);
	}

	void Material::Set4(const std::string& name, Vector4<float> value)
	{
		int location = m_shader.GetUniformLocation(name);
		glUniform4f(location, value.x, value.y, value.z, value.w);
	}

	void Material::Set3(const std::string& name, Vector3<int> value)
	{
		int location = m_shader.GetUniformLocation(name);
		glUniform3i(location, value.x, value.y, value.z);
	}

	void Material::Set3(const std::string& name, Vector3<unsigned int> value)
	{
		int location = m_shader.GetUniformLocation(name);
		glUniform3ui(location, value.x, value.y, value.z);
	}

	void Material::Set3(const std::string& name, Vector3<float> value)
	{
		int location = m_shader.GetUniformLocation(name);
		glUniform3f(location, value.x, value.y, value.z);
	}

	void Material::Set2(const std::string& name, Vector2<int> value)
	{
		int location = m_shader.GetUniformLocation(name);
		glUniform2i(location, value.x, value.y);
	}

	void Material::Set2(const std::string& name, Vector2<unsigned int> value)
	{
		int location = m_shader.GetUniformLocation(name);
		glUniform2ui(location, value.x, value.y);
	}

	void Material::Set2(const std::string& name, Vector2<float> value)
	{
		int location = m_shader.GetUniformLocation(name);
		glUniform2f(location, value.x, value.y);
	}

	void Material::Set(const std::string& name, int value)
	{
		int location = m_shader.GetUniformLocation(name);
		glUniform1i(location, value);
	}

	void Material::Set(const std::string& name, unsigned int value)
	{
		int location = m_shader.GetUniformLocation(name);
		glUniform1ui(location, value);
	}

	void Material::Set(const std::string& name, float value)
	{
		int location = m_shader.GetUniformLocation(name);
		glUniform1ui(location, value);
	}
}
