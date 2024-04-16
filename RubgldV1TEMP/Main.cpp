#include"RubgldOpenGL.h"

int main() { 
	RubgldOpenGL OpenGLRenderer = RubgldOpenGL();

	OpenGLRenderer.initOpenGL(3);
	OpenGLRenderer.initOpenGLWindow(1200, 800, "OpenGL App");

	Camera camera = Camera(glm::vec3(0,0,-10), glm::vec3(0,0,0));

	camera.config.backfaceCulling = false;
	camera.config.orthographic = true;
	camera.config.wireframe = false;
	camera.config.orthoConfig.panLook = true;

	camera.config.orthoConfig.size = 35;
	camera.config.orthoConfig.background = Texture("Background_Pink", GL_NEAREST, false).textureData.ID;

	Shader shader = Shader("EntityVertexShader.vert", "EntityFragmentShader.frag");

	Model model = Model(Mesh(LoadQuad()), Texture("UV_TEST.png", GL_NEAREST, true));
	Entity entity = Entity(glm::vec3(0,0,0), glm::vec3(0,0,0), glm::vec3(5,5,5), model, shader);

	while (!glfwWindowShouldClose(OpenGLRenderer.mainWindow)) {
		entity.rotate(glm::vec3(0,0,1), 0.05f);
		camera.updateCameraOrtho();

		OpenGLRenderer.processEntity(entity);
		OpenGLRenderer.updateOpenGL(camera);
	}

	shader.destroy();
	OpenGLRenderer.terminate();

	return 0;
}