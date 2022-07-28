#include "material.h"
#include "glad/glad.h"

template<typename T>
static void SetUniform(std::unordered_map<int, T>& map, int key, T& value)
{
	if (map.find(key) == map.end())
	{
		map.insert({ key, value });
	}
	else
	{
		map[key] = value;
	}
}

namespace ROGLL
{
	Material::Material(const Shader& shader)
		: m_shader(shader),
		m_uniformsF4(),
		m_uniformsF3(),
		m_uniformsF2(),
		m_uniformsF1(),
		m_uniformsI4(),
		m_uniformsI3(),
		m_uniformsI2(),
		m_uniformsI1(),
		m_uniformsUI4(),
		m_uniformsUI3(),
		m_uniformsUI2(),
		m_uniformsUI1()
	{}

#define BindUniformsV1(map, func) for (auto pair : (map)) {\
	const auto& vec = pair.second;\
	(func)(pair.first, vec.x);\
}\

#define BindUniformsV2(map, func) for (auto pair : (map)) {\
	const auto& vec = pair.second;\
	(func)(pair.first, vec.x, vec.y);\
}\

#define BindUniformsV3(map, func) for (auto pair : (map)) {\
	const auto& vec = pair.second;\
	(func)(pair.first, vec.x, vec.y, vec.z);\
}\

#define BindUniformsV4(map, func) for (auto pair : (map)) {\
	const auto& vec = pair.second;\
	(func)(pair.first, vec.x, vec.y, vec.z, vec.w);\
}\

	void Material::Bind() const
	{
		m_shader.Bind();

		BindUniformsV4(m_uniformsF4, glUniform4f);
		BindUniformsV3(m_uniformsF3, glUniform3f);
		BindUniformsV2(m_uniformsF2, glUniform2f);
		BindUniformsV1(m_uniformsF1, glUniform1f);

		BindUniformsV4(m_uniformsI4, glUniform4i);
		BindUniformsV3(m_uniformsI3, glUniform3i);
		BindUniformsV2(m_uniformsI2, glUniform2i);
		BindUniformsV1(m_uniformsI1, glUniform1i);

		BindUniformsV4(m_uniformsUI4, glUniform4ui);
		BindUniformsV3(m_uniformsUI3, glUniform3ui);
		BindUniformsV2(m_uniformsUI2, glUniform2ui);
		BindUniformsV1(m_uniformsUI1, glUniform1ui);
	}

	void Material::Unbind() const
	{
		m_shader.Unbind();
	}

	void Material::Set4(const std::string& name, Vector4<int> value)
	{
		int location = m_shader.GetUniformLocation(name);
		SetUniform(m_uniformsI4, location, value);
	}

	void Material::Set4(const std::string& name, Vector4<unsigned int> value)
	{
		int location = m_shader.GetUniformLocation(name);
		SetUniform(m_uniformsUI4, location, value);
	}

	void Material::Set4(const std::string& name, Vector4<float> value)
	{
		int location = m_shader.GetUniformLocation(name);
		SetUniform(m_uniformsF4, location, value);
	}

	void Material::Set3(const std::string& name, Vector3<int> value)
	{
		int location = m_shader.GetUniformLocation(name);
		SetUniform(m_uniformsI3, location, value);
	}

	void Material::Set3(const std::string& name, Vector3<unsigned int> value)
	{
		int location = m_shader.GetUniformLocation(name);
		SetUniform(m_uniformsUI3, location, value);
	}

	void Material::Set3(const std::string& name, Vector3<float> value)
	{
		int location = m_shader.GetUniformLocation(name);
		SetUniform(m_uniformsF3, location, value);
	}

	void Material::Set2(const std::string& name, Vector2<int> value)
	{
		int location = m_shader.GetUniformLocation(name);
		SetUniform(m_uniformsI2, location, value);
	}

	void Material::Set2(const std::string& name, Vector2<unsigned int> value)
	{
		int location = m_shader.GetUniformLocation(name);
		SetUniform(m_uniformsUI2, location, value);
	}

	void Material::Set2(const std::string& name, Vector2<float> value)
	{
		int location = m_shader.GetUniformLocation(name);
		SetUniform(m_uniformsF2, location, value);
	}

	void Material::Set(const std::string& name, Vector1<int> value)
	{
		int location = m_shader.GetUniformLocation(name);
		SetUniform(m_uniformsI1, location, value);
	}

	void Material::Set(const std::string& name, Vector1<unsigned int> value)
	{
		int location = m_shader.GetUniformLocation(name);
		SetUniform(m_uniformsUI1, location, value);
	}

	void Material::Set(const std::string& name, Vector1<float> value)
	{
		int location = m_shader.GetUniformLocation(name);
		SetUniform(m_uniformsF1, location, value);
	}
}
