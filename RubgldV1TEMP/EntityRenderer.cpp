#include"EntityRenderer.h"
void handleUniforms(Shader shader, Entity entity, Camera camera);



void EntityRenderer::drawEntityVector(std::vector<Entity>& entities, Camera camera) {
	for (int i = 0; i < entities.size(); i++) {
		Entity entity = entities.at(i);
		Mesh mesh = entities.at(i).entityData.model.modelData.mesh;
		Model model = entities.at(i).entityData.model;
		Texture texture0 = entities.at(i).entityData.model.modelData.texture0;

		texture0.activate(0);
		
		if (camera.config.backfaceCulling)
			glEnable(GL_CULL_FACE);
		else
			glDisable(GL_CULL_FACE);

		if (camera.config.wireframe) {
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			glDisable(GL_CULL_FACE);
		}	

		entity.entityData.shader.activate();
			entity.updateMatrices();
			handleUniforms(entity.entityData.shader, entity, camera);
			glBindTexture(GL_TEXTURE_2D, texture0.textureData.ID);
				glBindVertexArray(mesh.meshData.VAO.ID);
					glDrawElements(GL_TRIANGLES, mesh.meshData.indices.size(), GL_UNSIGNED_INT, 0);
				glBindVertexArray(0);
		entity.entityData.shader.terminate();
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
}

void EntityRenderer::drawOrthoBackground(GLuint textureID) {

}

void handleUniforms(Shader shader, Entity entity, Camera camera){
	GLuint uniID = glGetUniformLocation(shader.ID, "scale");
	glUniform1f(uniID, entity.entityData.model.modelData.mesh.config.Scale);
	
	GLuint texture0ID = glGetUniformLocation(shader.ID, "texture0");
	glUniform1i(texture0ID, 0);

	int modelMatrixID = glGetUniformLocation(shader.ID, "modelMatrix");
	glUniformMatrix4fv(modelMatrixID, 1, GL_FALSE, glm::value_ptr(entity.entityData.modelMatrix));

	int viewMatrixID = glGetUniformLocation(shader.ID, "viewMatrix");
	glUniformMatrix4fv(viewMatrixID, 1, GL_FALSE, glm::value_ptr(camera.cameraData.viewMatrix));

	int projectionMatrixID = glGetUniformLocation(shader.ID, "projectionMatrix");
	if (!camera.config.orthographic)
		glUniformMatrix4fv(projectionMatrixID, 1, GL_FALSE, glm::value_ptr(camera.cameraData.projectionMatrixPerspective));
	else
		glUniformMatrix4fv(projectionMatrixID, 1, GL_FALSE, glm::value_ptr(camera.cameraData.projectionMatrixOrtho));
}