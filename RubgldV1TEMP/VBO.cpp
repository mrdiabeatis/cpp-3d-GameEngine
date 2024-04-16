#include "VBO.h"

VBO::VBO(std::vector<GLfloat>& vertexData) {
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ARRAY_BUFFER, ID);
	glBufferData(GL_ARRAY_BUFFER, vertexData.size() * sizeof(GLfloat), vertexData.data(), GL_STATIC_DRAW);
	terminateVertex();
}

VBO::VBO(std::vector<GLuint>& indexData) {
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexData.size() * sizeof(GLuint), indexData.data(), GL_STATIC_DRAW);
	terminateIndex();
}

void VBO::activateVertex() {
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void VBO::terminateVertex() {
	glBindBuffer(GL_ARRAY_BUFFER, ID);
}

void VBO::destroyVertex() {
	glDeleteBuffers(1, &ID);
}

void VBO::activateIndex() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

void VBO::terminateIndex() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void VBO::destroyIndex() {
	glDeleteBuffers(1, &ID);
}