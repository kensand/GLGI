#include "stdafx.h"
#include "GLGI.h"

GLGI::Window * GLGI::Window::currentWindow = 0;
void GLGI::Window::cursorPosCallBack(GLFWwindow* window, double xpos, double ypos)
{
	currentWindow->mouseX = xpos;
	currentWindow->mouseY = ypos;

}


// This is the constructor of a class that has been exported.
// see GLGI.h for the class definition
GLGI::Window::Window()
{
	this->mouseX = 0.;
	this->mouseY = 0.;
	if (!glfwInit())
		throw("GLFW init Failure");
	//glfwOpenWindowHint(GLFW::GLFW_FSAA_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	/* Create a windowed mode window and its OpenGL context */
	glfwwindow = glfwCreateWindow(1440, 900, "Hello World", NULL, NULL);
	if (!glfwwindow)
	{
		glfwTerminate();
		throw("GLFW window creation failed;");
	}
	glfwSetWindowUserPointer(glfwwindow, this);
	glfwSetCursorPosCallback(glfwwindow, &(cursorPosCallBack));
	makeCurrentContext();

	glewExperimental = GL_TRUE;
	if (glewInit()) {
		//DBOUT("glew init Failure");
		throw("glew init Failure");
	}
	input = new InputManager(this);


	//TODO make these functions variable via interface



}

GLGI::Window::~Window() {
	delete input;
}


bool GLGI::Window::shouldClose() {
	return glfwWindowShouldClose(glfwwindow);
}

void GLGI::Window::close() {
	glfwTerminate();
}
void GLGI::Window::makeCurrentContext() {
	glfwMakeContextCurrent(glfwwindow);
}

void GLGI::Window::draw() {
	/* Render here */
	glClear(GL_COLOR_BUFFER_BIT);

	/* Swap front and back buffers */
	glfwSwapBuffers(glfwwindow);

	/* Poll for and process events */
	glfwPollEvents();
}

GLGI::InputManager * GLGI::Window::createInputManager()
{
	InputManager * temp = input;
	input = nullptr;
	if (temp != nullptr) {
		temp->detach();
	}
	input = new InputManager(this);
	return temp;
	
}

GLGI::InputManager * GLGI::Window::detachInputManager()
{
	GLGI::InputManager * temp = input;
	input = nullptr;
	if (temp != nullptr) {
		temp->detach();
	}
	return temp;

}

void GLGI::Window::setMouseState(int state)
{
	if (!((state == GLGI_CURSOR_HIDDEN) || (state == GLGI_CURSOR_NORMAL) || (state == GLGI_CURSOR_DISABLED))) {
		throw("ERROR: Cursor state is invalid.");
	}
	else {
		mouseState = glfwGetInputMode(glfwwindow, GLFW_CURSOR);
		if (mouseState != state) {
			mouseState = state;
			glfwSetInputMode(glfwwindow, GLFW_CURSOR, mouseState);
		}
	}
}
