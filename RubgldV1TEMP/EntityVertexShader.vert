#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 uvs;

out vec2 texCoord;

uniform float scale;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main() {
	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(position, 1.0);
	texCoord = uvs;
}