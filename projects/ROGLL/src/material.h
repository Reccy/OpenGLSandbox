#pragma once
#include "shader.h"
#include "vector.h"
#include <iostream>
#include <unordered_map>

namespace ROGLL
{
	class Material
	{
	private:
		template<typename T>
		using Vec1Uniforms = std::unordered_map<int, Vector1<T>>;

		template<typename T>
		using Vec2Uniforms = std::unordered_map<int, Vector2<T>>;

		template<typename T>
		using Vec3Uniforms = std::unordered_map<int, Vector3<T>>;

		template<typename T>
		using Vec4Uniforms = std::unordered_map<int, Vector4<T>>;
	public:
		Material(const Shader& shader);

		void Bind() const;
		void Unbind() const;

		void Set4(const std::string& name, Vector4<int> value);
		void Set4(const std::string& name, Vector4<unsigned int> value);
		void Set4(const std::string& name, Vector4<float> value);

		void Set3(const std::string& name, Vector3<int> value);
		void Set3(const std::string& name, Vector3<unsigned int> value);
		void Set3(const std::string& name, Vector3<float> value);

		void Set2(const std::string& name, Vector2<int> value);
		void Set2(const std::string& name, Vector2<unsigned int> value);
		void Set2(const std::string& name, Vector2<float> value);

		void Set(const std::string& name, Vector1<int> value);
		void Set(const std::string& name, Vector1<unsigned int> value);
		void Set(const std::string& name, Vector1<float> value);
	private:
		const Shader& m_shader;

		Vec4Uniforms<float> m_uniformsF4;
		Vec3Uniforms<float> m_uniformsF3;
		Vec2Uniforms<float> m_uniformsF2;
		Vec1Uniforms<float> m_uniformsF1;

		Vec4Uniforms<int> m_uniformsI4;
		Vec3Uniforms<int> m_uniformsI3;
		Vec2Uniforms<int> m_uniformsI2;
		Vec1Uniforms<int> m_uniformsI1;

		Vec4Uniforms<unsigned int> m_uniformsUI4;
		Vec3Uniforms<unsigned int> m_uniformsUI3;
		Vec2Uniforms<unsigned int> m_uniformsUI2;
		Vec1Uniforms<unsigned int> m_uniformsUI1;
	};
}
