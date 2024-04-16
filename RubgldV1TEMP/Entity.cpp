#include"Entity.h"

Entity::Entity(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale, Model model, Shader shader) {
	transform.position = position;
	transform.rotation = rotation;
	transform.scale = scale;
	entityData.model = model;
	entityData.shader = shader;
}

void Entity::updateMatrices() {
	entityData.modelMatrix = glm::translate(entityData.modelMatrix, transform.position);
	entityData.modelMatrix = glm::rotate(entityData.modelMatrix, glm::radians(transform.rotation.y), glm::vec3(0,1,0));
	entityData.modelMatrix = glm::rotate(entityData.modelMatrix, glm::radians(transform.rotation.x), glm::vec3(1,0,0));
	entityData.modelMatrix = glm::rotate(entityData.modelMatrix, glm::radians(transform.rotation.z), glm::vec3(0,0,1));
	entityData.modelMatrix = glm::scale(entityData.modelMatrix, transform.scale);
}

void Entity::rotate(glm::vec3 dir, float mag) {
	transform.rotation += dir * mag;
}

void Entity::destroy() {
	entityData.model.destroy();
	entityData.model.modelData.texture0.destroy();
}