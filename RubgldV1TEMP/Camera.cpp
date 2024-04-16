#include"Camera.h"

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\n\0";

Camera::Camera(glm::vec3 position, glm::vec3 rotation) {
	transform.position = position;
	transform.rotation = rotation;
}

void Camera::updateMatrices(float ScreenWIDTH, float ScreenHEIGHT) {
	cameraData.viewMatrix = viewMatrix();

	cameraData.projectionMatrixPerspective = projectionMatrixPerspective(ScreenWIDTH, ScreenHEIGHT);
	cameraData.projectionMatrixOrtho = projectionMatrixOrtho(ScreenWIDTH, ScreenHEIGHT);
}

void Camera::renderCameraBackground() {
	bool init = true;

	if (config.orthographic) {
		if (init) {
			config.orthoConfig.orthoData.backgroundVertexShader = glCreateShader(GL_VERTEX_SHADER);
			
			glShaderSource(config.orthoConfig.orthoData.backgroundVertexShader, 1, &vertexShaderSource, NULL);
			glCompileShader(config.orthoConfig.orthoData.backgroundVertexShader);


			config.orthoConfig.orthoData.backgroundFragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

			glShaderSource(config.orthoConfig.orthoData.backgroundFragmentShader, 1, &fragmentShaderSource, NULL);
			glCompileShader(config.orthoConfig.orthoData.backgroundFragmentShader);

			config.orthoConfig.orthoData.backgroundShaderProgram = glCreateProgram();
			
			glAttachShader(config.orthoConfig.orthoData.backgroundShaderProgram, config.orthoConfig.orthoData.backgroundVertexShader);
			glAttachShader(config.orthoConfig.orthoData.backgroundShaderProgram, config.orthoConfig.orthoData.backgroundFragmentShader);
	
			glLinkProgram(config.orthoConfig.orthoData.backgroundShaderProgram);

			glDeleteShader(config.orthoConfig.orthoData.backgroundVertexShader);
			glDeleteShader(config.orthoConfig.orthoData.backgroundFragmentShader);

			GLfloat vertices[] =
			{
				-1, -1 * float(sqrt(3)) / 3, 0.0f, // Lower left corner
				1, -1 * float(sqrt(3)) / 3, 0.0f, // Lower right corner
				0.0f, 1 * float(sqrt(3)) * 2 / 3, 0.0f, // Upper corner
				-1 / 2, 1 * float(sqrt(3)) / 6, 0.0f, // Inner left
				1 / 2, 1 * float(sqrt(3)) / 6, 0.0f, // Inner right
				0.0f, -1 * float(sqrt(3)) / 3, 0.0f // Inner down
			};

			GLuint indices[] =
			{
				0, 3, 5, // Lower left triangle
				3, 2, 4, // Upper triangle
				5, 4, 1 // Lower right triangle
			};

			glGenVertexArrays(1, &config.orthoConfig.orthoData.VAO);
			glGenBuffers(1, &config.orthoConfig.orthoData.VBO);
			glGenBuffers(1, &config.orthoConfig.orthoData.EBO);

			glBindVertexArray(config.orthoConfig.orthoData.VAO);

			glBindBuffer(GL_ARRAY_BUFFER, config.orthoConfig.orthoData.VBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, config.orthoConfig.orthoData.EBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
			glEnableVertexAttribArray(0);

			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindVertexArray(0);
			
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
		}

		glUseProgram(config.orthoConfig.orthoData.backgroundShaderProgram);
			glBindVertexArray(config.orthoConfig.orthoData.VAO);
				glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}
	init = false;
}

void Camera::updateCameraPerspective() {

}

void Camera::updateCameraOrtho() {

}

glm::mat4 Camera::viewMatrix() {
	glm::mat4 result = glm::mat4(1.0);
	result = glm::translate(result, transform.position);
	result = glm::rotate(result, glm::radians(transform.rotation.y), glm::vec3(0,1,0));
	result = glm::rotate(result, glm::radians(transform.rotation.x), glm::vec3(1,0,0));
	result = glm::rotate(result, glm::radians(transform.rotation.z), glm::vec3(0,0,1));
	return result;
}

glm::mat4 Camera::projectionMatrixPerspective(float ScreenWIDTH, float ScreenHEIGHT) {
	glm::mat4 result = glm::mat4(1.0);
	result = glm::perspective(glm::radians(config.perspectiveConfig.FOV), (float)(ScreenWIDTH/ScreenHEIGHT), 0.001f, config.perspectiveConfig.farPlane);
	return result;
}

glm::mat4 Camera::projectionMatrixOrtho(float ScreenWIDTH, float ScreenHEIGHT) {
	glm::mat4 result = glm::mat4(1.0);
	result = glm::ortho(
		(-ScreenWIDTH * config.orthoConfig.size)/1000, (ScreenWIDTH * config.orthoConfig.size)/1000,
		(-ScreenHEIGHT * config.orthoConfig.size)/1000, (ScreenHEIGHT * config.orthoConfig.size)/1000,
		0.001f, config.orthoConfig.farPlane);
	return result;
}
