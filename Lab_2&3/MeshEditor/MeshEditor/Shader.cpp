#include "Shader.h"
#include "glad.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

Shader::Shader(const char* vertexFilePath, const char* fragmentFilePath)
{
	shaderProgramId = compileShaders(vertexFilePath, fragmentFilePath);
}

unsigned int Shader::getId() { return shaderProgramId;  };

void Shader::use()
{
	glUseProgram(shaderProgramId);
}

void Shader::setBool(const std::string& name, bool value) const
{
	glUniform1i(glGetUniformLocation(shaderProgramId, name.c_str()), (int)value);
}

void Shader::setInt(const std::string& name, int value) const
{
	glUniform1i(glGetUniformLocation(shaderProgramId, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value) const
{
	glUniform1f(glGetUniformLocation(shaderProgramId, name.c_str()), value);
}

void Shader::setVec3(const std::string& name, float x, float y, float z) const
{
	glUniform3f(glGetUniformLocation(shaderProgramId, name.c_str()), x, y, z);
}

unsigned int Shader::compileShaders(const char* vertexFilePath, const char* fragmentFilePath)
{
	const char* vertexShaderCode;
	const char* fragmentShaderCode;

	std::string strVertexShaderCode;
	std::ifstream vertexShaderStream(vertexFilePath, std::ios::in);
	if (vertexShaderStream.is_open())
	{
		std::stringstream sstr;
		sstr << vertexShaderStream.rdbuf();
		strVertexShaderCode = sstr.str();
		vertexShaderStream.close();
	}

	std::string strFragmentShaderCode;
	std::ifstream fragmentShaderStream(fragmentFilePath, std::ios::in);
	if (fragmentShaderStream.is_open())
	{
		std::stringstream sstr;
		sstr << fragmentShaderStream.rdbuf();
		strFragmentShaderCode = sstr.str();
		fragmentShaderStream.close();
	}

	vertexShaderCode = strVertexShaderCode.c_str();
	fragmentShaderCode = strFragmentShaderCode.c_str();

	unsigned int vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vertexShaderCode, NULL);
	glCompileShader(vertex);
	checkForError(vertex, ErrorType::Vertex);

	unsigned int fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fragmentShaderCode, NULL);
	glCompileShader(fragment);
	checkForError(fragment, ErrorType::Fragment);

	unsigned int programId = glCreateProgram();
	glAttachShader(programId, vertex);
	glAttachShader(programId, fragment);
	glLinkProgram(programId);
	checkForError(programId, ErrorType::Program);

	glDeleteShader(vertex);
	glDeleteShader(fragment);

	return programId;
}

void Shader::checkForError(unsigned int shader, ErrorType type)
{
	int compileStatus;
	char infoLog[1024];

	if (type == ErrorType::Program)
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &compileStatus);

		if (compileStatus) return;

		glGetProgramInfoLog(shader, 1024, NULL, infoLog);
		std::cout << "Error: Program link error:\n" << infoLog << "\n" << std::endl;
	}
	else 
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &compileStatus);

		if (compileStatus) return;

		glGetProgramInfoLog(shader, 1024, NULL, infoLog);

		if (type == ErrorType::Vertex)
			std::cout << "Error: Vertex compile error:\n" << infoLog << "\n" << std::endl;
		else
			std::cout << "Error: Fragment compile error:\n" << infoLog << "\n" << std::endl;
	}
}