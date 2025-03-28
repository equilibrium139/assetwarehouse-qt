#ifndef SHADER_H
#define SHADER_H

#include <QOpenGLFunctions_4_3_Core>

#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

#include <glm/gtc/type_ptr.hpp>

class Shader : protected QOpenGLFunctions_4_3_Core
{
public:
	unsigned int id;
	static constexpr int maxPointLights = 5;
	static constexpr int maxSpotLights = 5;
	static constexpr int maxDirLights = 5;
	Shader(const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr, const std::vector<std::string>& defines = {});


	void Use();

	void SetBool(const char* name, bool value);
	void SetInt(const char* name, int value);
	void SetIntArray(const char* name, int* values, unsigned int count);
	void SetUint(const char* name, std::uint32_t value);
	void SetFloat(const char* name, float value);
	void SetMat4(const char* name, const float* value);
	void SetMat4(const char* name, const float* value, int count);
	void SetMat4(const char* name, const glm::mat4& m);
	void SetMat3(const char* name, const float* value);
	void SetMat3(const char* name, const glm::mat3& m);
	void SetVec2(const char* name, float x, float y);
	void SetVec3(const char* name, float x, float y, float z);
	void SetVec3(const char* name, const glm::vec3& vec);
	void SetVec4(const char* name, float x, float y, float z, float w);
	void SetVec4(const char* name, const glm::vec4& vec);
	void SetVec3Array(const char* name, float* values, unsigned int count);
private:
	std::string get_file_contents(const char* path);
	std::unordered_map<std::string, int> cachedUniformLocations;

	int GetUniformLocation(const std::string& name)
	{
		auto iter = cachedUniformLocations.find(name);
		if (iter != cachedUniformLocations.end())
		{
			return iter->second;
		}
        int location = glGetUniformLocation(id, name.c_str());
		if (location < 0)
		{
			std::cerr << "Warning: GetUniformLocation attempting to access invalid uniform '" << name << "'\n";
		}
		//assert(location >= 0);
		cachedUniformLocations[name] = location;
		return location;
	}
};

#endif // !SHADER_H
