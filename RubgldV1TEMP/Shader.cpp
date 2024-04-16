#include "Shader.h"

Shader::Shader(const char* vertex, const char* fragment) {
	std::string vs = loadShaderAsCharPtr(vertex).c_str();
	vertexShaderSource = vs.c_str();
	std::string fs = loadShaderAsCharPtr(fragment).c_str();
	fragmentShaderSource = fs.c_str();
	
	if (vs != "")
		std::cout << "MSG::SHADERFILESLOADED\n";

	// create and compile vertexShader
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	// create and compile fragmentShader
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	// create shaderProgram from shaders
	ID = glCreateProgram();
	glAttachShader(ID, vertexShader);
	glAttachShader(ID, fragmentShader);

	glLinkProgram(ID);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	std::cout << "MSG::SHADERCREATED\n";
}

void Shader::activate() {
	glUseProgram(ID);
}

void Shader::terminate() {
	glUseProgram(0);
}

void Shader::destroy() {
	std::cout << "MSG::SHADERDESTROYED\n";
	glDeleteProgram(ID);
}
