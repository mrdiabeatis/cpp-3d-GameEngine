#include "RubgldOpenGL.h"

std::vector <Entity> Entities;
EntityRenderer entityRenderer = EntityRenderer();

DebugGUI debugGUI = DebugGUI();

void RubgldOpenGL::initOpenGL(int Version) {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, Version);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, Version);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, false);
	std::cout << "MSG::OPENGLCONTEXTCREATED\n";
}

void RubgldOpenGL::initOpenGLWindow(float SizeX, float SizeY, const char* name) {
	GLFWwindow* window = glfwCreateWindow(SizeX, SizeY, name, NULL, NULL);
	if (window == nullptr) 
		throw std::invalid_argument("ERR::WINDOWCREATIONFAILED\n");
	mainWindow = window;
	std::cout << "MSG::WINDOWCREATED\n";
	glfwMakeContextCurrent(window);
	gladLoadGL();
	glViewport(0, 0, SizeX, SizeY);
	glEnable(GL_DEPTH_TEST);
	WIDTH = SizeX;
	HEIGHT = SizeY;
	io = debugGUI.initDebugGUI(window);
	std::cout << "MSG::MAINVIEWPORTCREATED\n";
}

void RubgldOpenGL::updateOpenGL(Camera camera) {
	// clear frameBuffers
	if (initialFrame) {
		clearColor[0] = camera.config.clearColor.x;
		clearColor[1] = camera.config.clearColor.y;
		clearColor[2] = camera.config.clearColor.z;
		clearColor[3] = 1.0f;
	}
	
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	ImGui::Begin("Bingus");
	ImGui::End();

	glClearColor(
		clearColor[0],
		clearColor[1],
		clearColor[2], 
		clearColor[3]
	);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// manual drawCalls go here... 
	camera.updateMatrices(WIDTH, HEIGHT);
	entityRenderer.drawEntityVector(Entities, camera);
	Entities.clear();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	// update window events such as resizing and etc. [updateOpenGL (after opaque rendering)]
	glfwSwapBuffers(mainWindow);
	glfwPollEvents();
	initialFrame = false;
}

void RubgldOpenGL::terminate() {
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(mainWindow);
	glfwTerminate();
	std::cout << "MSG::SHUTDOWNOPERATIONSCOMPLETED\n";
}

void RubgldOpenGL::processEntity(Entity entity) {
	Entities.push_back(entity);
}