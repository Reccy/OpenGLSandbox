#pragma once
#include "shader.h"
#include <iostream>

namespace ROGLL
{
	template<typename T>
	struct Vector4 {
		T x, y, z, w;
	};

	template<typename T>
	struct Vector3 {
		T x, y, z;
	};

	template<typename T>
	struct Vector2 {
		T x, y;
	};

	class Material
	{
	public:
		Material() = delete;

		Material(const Shader& shader);

		void Set4(const std::string& name, Vector4<int> value);
		void Set4(const std::string& name, Vector4<unsigned int> value);
		void Set4(const std::string& name, Vector4<float> value);

		void Set3(const std::string& name, Vector3<int> value);
		void Set3(const std::string& name, Vector3<unsigned int> value);
		void Set3(const std::string& name, Vector3<float> value);

		void Set2(const std::string& name, Vector2<int> value);
		void Set2(const std::string& name, Vector2<unsigned int> value);
		void Set2(const std::string& name, Vector2<float> value);

		void Set(const std::string& name, int value);
		void Set(const std::string& name, unsigned int value);
		void Set(const std::string& name, float value);
	private:
		const Shader& m_shader;
	};
}
