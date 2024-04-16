#include"Model.h"

Model::Model(Mesh mesh, Texture texture0) {
	modelData.texture0 = texture0;
	modelData.mesh = mesh;
}

void Model::destroy() {
	glDeleteTextures(1, &modelData.texture0.textureData.ID);
	glDeleteVertexArrays(1, &modelData.mesh.meshData.VAO.ID);
}