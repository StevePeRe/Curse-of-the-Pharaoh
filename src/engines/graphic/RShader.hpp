#pragma once

// Instalar glad
#include <string>
#include <fstream>
#include <sstream>

#include <engines/graphic/Resource.hpp>
#include <glm/glm.hpp>
#include <GLAD/src/glad.h>

#define shader_path "./media/shaders/"
#define shader_ext_vs ".vs"
#define shader_ext_fs ".fs"

struct RShader : public Resource
{
public:
    // Resource* loadResource(std::string  filename); //{ this->setName(filename); return nullptr; };
    unsigned int ID{};
    // constructor generates the shader on the fly
    RShader(){};
    RShader(std::string filename);
    void loadResource(std::string filename)
    {
        this->setName(filename);
        loadShader(filename);
    };
    void loadShader(std::string filename);
    // activate the shader
    void use();
    // utility uniform functions
    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
    void setVec2(const std::string &name, const glm::vec2 &value) const;
    void setVec2(const std::string &name, float x, float y) const;
    void setVec3(const std::string &name, const glm::vec3 &value) const;
    void setVec3(const std::string &name, float x, float y, float z) const;
    void setVec4(const std::string &name, const glm::vec4 &value) const;
    void setVec4(const std::string &name, float x, float y, float z, float w);
    void setMat2(const std::string &name, const glm::mat2 &mat) const;
    void setMat3(const std::string &name, const glm::mat3 &mat) const;
    void setMat4(const std::string &name, const glm::mat4 &mat) const;

private:
    // utility function for checking shader compilation/linking errors.
    void checkCompileErrors(GLuint shader, std::string type);
};
