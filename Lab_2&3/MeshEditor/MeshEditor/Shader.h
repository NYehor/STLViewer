#pragma once
#include <string>
#include <iostream>

class Shader
{
public:
    Shader(const char* vertexFilePath, const char* fragmentFilePath);

    void use();
    
    void setBool(const std::string& name, bool value) const;
    void setInt(const std::string& name, int value) const;
    void setFloat(const std::string& name, float value) const;
    void setVec3(const std::string& name, float x, float y, float z) const;

    unsigned int getId();

private:
    enum class ErrorType
    {
        Vertex = 0,
        Fragment = 1,
        Program = 2,
    };

    unsigned int shaderProgramId;
    unsigned int compileShaders(const char* vertexFilePath, const char* fragmentFilePath);
    void checkForError(unsigned int shader, ErrorType type);
};
