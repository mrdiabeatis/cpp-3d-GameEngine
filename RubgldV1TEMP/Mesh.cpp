#include"Mesh.h"

Mesh::Mesh(std::vector <GLfloat>& vertices, std::vector <GLuint>& indices, std::vector <GLfloat>& uvs) {
	meshData.vertices = vertices;
	meshData.indices = indices;
	meshData.uvs = uvs;
	meshData.VAO = VAO();

	meshData.VAO.activate();

	VBO _VBO1 = VBO(meshData.vertices);
	VBO _VBO2 = VBO(meshData.uvs);

	VBO _EBO = VBO(meshData.indices);

	_VBO1.activateVertex();
	_VBO2.activateVertex();
	_EBO.activateIndex();

	meshData.VAO.LinkAttrib(_VBO1, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);
	meshData.VAO.LinkAttrib(_VBO2, 1, 2, GL_FLOAT, 2 * sizeof(float), (void*)0);

	meshData.VAO.terminate();
	_VBO1.terminateVertex();
	_VBO2.terminateVertex();
	_EBO.terminateIndex();
}

Mesh::Mesh(vertexDataStream v) {
	meshData.vertices = v.vertices;
	meshData.indices = v.indices;
	meshData.uvs = v.uvs;
	meshData.VAO = VAO();

	meshData.VAO.activate();

	VBO _VBO1 = VBO(meshData.vertices);
	VBO _VBO2 = VBO(meshData.uvs);

	VBO _EBO = VBO(meshData.indices);

	_VBO1.activateVertex();
	_VBO2.activateVertex();
	_EBO.activateIndex();

	meshData.VAO.LinkAttrib(_VBO1, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);
	meshData.VAO.LinkAttrib(_VBO2, 1, 2, GL_FLOAT, 2 * sizeof(float), (void*)0);

	meshData.VAO.terminate();
	_VBO1.terminateVertex();
	_VBO2.terminateVertex();
	_EBO.terminateIndex();
}
