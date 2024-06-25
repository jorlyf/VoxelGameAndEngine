#pragma once
#include <cstdint>
#include <string>
#include <glm/glm.hpp>

namespace vx
{
	class Shader {
	public:
		Shader(const uint32_t id);
		~Shader();

		static Shader* loadFromFile(const std::string& vertexFilePath, const std::string& fragmentFilePath);

		void use();
		void setUniformMatrix(const std::string& name, const glm::mat4& matrix);

	private:
		uint32_t _id;
	};
}
