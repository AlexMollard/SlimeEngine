#include "Application.h"

// Camera
Camera* camera = nullptr;
float lastX = xRES / 2.0f;
float lastY = yRES / 2.0f;
bool firstMouse = true;

// WindowSize
int windowWidth, windowHeight;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);


Application::~Application()
{
	delete camera;
}

int Application::Create()
{
	if (glfwInit() == false)
		return -1;

	window = glfwCreateWindow(xRES, yRES, "SlimeCore", nullptr, nullptr);

	if (window == nullptr)
	{
		glfwTerminate();
		return -2;
	}

	glfwMakeContextCurrent(window);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);

	windowWidth = xRES;
	windowHeight = yRES;

	if (ogl_LoadFunctions() == ogl_LOAD_FAILED)
	{
		glfwDestroyWindow(window);
		glfwTerminate();
		return -3;
	}

	// Graphic Card Driver version
	std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	glClearColor(0.15f, 0.15f, 0.15f, 1);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	projection = glm::perspective(glm::radians(45.0f), (float)windowWidth / (float)windowHeight, 0.1f, 100.0f);
	camera = new Camera(projection);
	projectionViewMat = &camera->ProjectionViewMat;
	return 1;
}

void Application::Update()
{
	processInput(window);
	Update_Window(window);
	camera->UpdateProjectionViewMatrix();
}

void Application::Update_Window(GLFWwindow* window)
{
	glfwSwapBuffers(window);
	glfwPollEvents();

	glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	now = glfwGetTime();
	delta = (float)(now - last);
	last = now;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glfwGetCurrentContext();
	glfwGetWindowSize(window, &width, &height);
	windowWidth = width;
	windowHeight = height;
	glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = (float)xpos;
		lastY = (float)ypos;
		firstMouse = false;
	}

	float xoffset = (float)xpos - lastX;
	float yoffset = lastY - (float)ypos;

	lastX = (float)xpos;
	lastY = (float)ypos;

	camera->ProcessMouseMovement(xoffset, yoffset);
}

void Application::processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera->ProcessKeyboard(FORWARD, delta);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera->ProcessKeyboard(BACKWARD, delta);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera->ProcessKeyboard(LEFT, delta);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera->ProcessKeyboard(RIGHT, delta);
}