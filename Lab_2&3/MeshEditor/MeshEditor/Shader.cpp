#include "Shader.h"
#include "glad.h"


Shader::Shader(const char* vertexShaderCode, const char* fragmentShaderCode)
{
	shaderProgramId = compileShaders(vertexShaderCode, fragmentShaderCode);
}

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
	glUniform1i(glGetUniformLocation(shaderProgramId, name.c_str()), (int)value);
}

void Shader::setFloat(const std::string& name, float value) const
{
	glUniform1i(glGetUniformLocation(shaderProgramId, name.c_str()), (int)value);
}

unsigned int Shader::compileShaders(const char* vertexShaderCode, const char* fragmentShaderCode)
{
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