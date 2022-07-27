#pragma once
#include <string>

namespace ROGLL
{
	class Shader
	{
	private:
		unsigned int m_shaderId;
	public:
		Shader(std::string sourceFilepath);

		void Bind() const;
		void Unbind() const;
	};
}