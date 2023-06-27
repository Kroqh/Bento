#pragma once

#include <string>

namespace Bento {

	class Shader {

	public:
		Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
		virtual ~Shader();

		void Bind() const;
		void Unbind() const;
	
	private:
		uint32_t m_RendererID;
	};

}