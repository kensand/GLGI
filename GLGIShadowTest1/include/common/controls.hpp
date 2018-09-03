#ifndef CONTROLS_HPP
#define CONTROLS_HPP
// Include GLFW
#include <GLFW/glfw3.h>
extern GLFWwindow* window; // The "extern" keyword here is to access the variable "window" declared in tutorialXXX.cpp. This is a hack to keep the tutorials simple. Please avoid this.
						   // Include GLM
#include <glm/glm.hpp>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/vector_angle.hpp>
using namespace glm;
#include <cmath>
//#define PI 3.14159265359f
//#include <common/controls.hpp>



#include <queue>








using namespace glm;


#include <common/shader.hpp>
#include <common/texture.hpp>

#include <common/objloader.hpp>
#include <common/vboindexer.hpp>






















/*
#include "Snake.hpp"

void endProgram() {
glfwTerminate();
exit(0);
}

void computeMatricesFromInputs(float aspect);
glm::mat4 getViewMatrix();
glm::mat4 getProjectionMatrix();





Snake * snake;
















float initialFoV = 90.0f;


glm::mat4 ViewMatrix;
glm::mat4 ProjectionMatrix;

glm::mat4 getViewMatrix() {
	return ViewMatrix;
}
glm::mat4 getProjectionMatrix() {
	return ProjectionMatrix;
}

glm::vec3 position = glm::vec3(2, 2, -2);
glm::vec3 moveDirection = glm::vec3(0, 0, -1);
glm::vec3 nextMoveDirection = glm::vec3(0, 0, -1);
glm::vec3 moveUp = glm::vec3(0, 1, 0);
glm::vec3 nextMoveUp = glm::vec3(0, 1, 0);

glm::vec3 baseLookDir = moveDirection;
glm::vec3 lookDir = moveDirection;
glm::vec3 lookUp = moveUp;


float verticalAngle = 0.f;
float horizontalAngle = 0.f;

double lastTime = glfwGetTime();

float moveSpeed = 4.f;
float moveMult = 1.001;
float capSpeed = 7.f;
float speedIncrease = 2.f;
bool increaseMoveSpeed = false;

glm::vec3 invert(glm::vec3 in) {
	return glm::vec3(in[0] * -1, in[1] * -1, in[2] * -1);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{

	
	if (key == GLFW_KEY_LEFT_SHIFT && action == GLFW_PRESS){// && !increaseMoveSpeed) {
		moveSpeed *= speedIncrease;
		//increaseMoveSpeed = true;
	}
	if (key == GLFW_KEY_LEFT_SHIFT && action == GLFW_RELEASE){// && increaseMoveSpeed) {
		moveSpeed /= speedIncrease;
		//increaseMoveSpeed = false;
	}
	// Move forward
	if (key == GLFW_KEY_W && action == GLFW_PRESS) {
		glm::vec3 temp = invert(nextMoveDirection);
		nextMoveDirection = nextMoveUp;
		nextMoveUp = temp;

	}
	// Move backward
	if (key == GLFW_KEY_S && action == GLFW_PRESS) {
		glm::vec3 temp = nextMoveDirection;
		nextMoveDirection = invert(nextMoveUp);
		nextMoveUp = temp;
	}
	// Strafe right
	if (key == GLFW_KEY_D && action == GLFW_PRESS) {
		nextMoveDirection = cross(nextMoveDirection, nextMoveUp);
		
	}
	// Strafe left
	if (key == GLFW_KEY_A && action == GLFW_PRESS) {
		nextMoveDirection = invert(cross(nextMoveDirection, nextMoveUp));

	}

}
float mouseSpeed = 0.005f;
double lastMouseTime = glfwGetTime();
static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	// Reset mouse position for next frame
	glfwSetCursorPos(window, 1024 / 2, 768 / 2);
	// Direction : Spherical coordinates to Cartesian coordinates conversion
	// Compute new orientation
	horizontalAngle += mouseSpeed * float(1024 / 2 - xpos);
	horizontalAngle = fmod(horizontalAngle, 2 * PI);
	verticalAngle += mouseSpeed * float(768 / 2 - ypos);
	if (verticalAngle >= PI / 2 - .1)
		verticalAngle = PI / 2 - .1;
	if (verticalAngle <= -1 * PI / 2 + .1)
		verticalAngle = -1 * PI / 2 + .1;
	lastMouseTime = glfwGetTime();
}
float squareSize = 4.f;
float baseLookSpeed = 0.1f;
float baseLookSnap = 0.1f;

glm::vec3 lastCube;


void computeMatricesFromInputs(float aspect) {
	double time = glfwGetTime();
	glm::vec3 moved = glm::vec3(moveSpeed * (time - lastTime) * moveDirection[0], 
		moveSpeed * (time - lastTime) * moveDirection[1],
		moveSpeed * (time - lastTime) * moveDirection[2]);
	glm::vec3 nextPosition = position + moved;

	
	
	if (nextMoveDirection != moveDirection) {
		moveDirection = nextMoveDirection;
		moveUp = nextMoveUp;
		//this should be limited somehow, since using it continuously causes you to remain int the same position.
		nextPosition = glm::vec3(nextPosition[0] - fmod(nextPosition[0], squareSize) + 2.f, nextPosition[1] - fmod(nextPosition[1], squareSize) + 2.f, nextPosition[2] - fmod(nextPosition[2], squareSize) - 2.f);
		lastMouseTime = time - 1.f;
		//verticalAngle = 0.f;
		//horizontalAngle = 0.f;
	}
		

	

	if (lastCube != snake->toIndicies(nextPosition)) {
		if (nextPosition[0] >= 40 || nextPosition[0] < 0|| nextPosition[1] >= 40 || nextPosition[1] < 0 || nextPosition[2] <= -40 || nextPosition[2] > 0) {
			//outside boundries
			endProgram();
		}
		if (snake->isInSnake(snake->toIndicies(nextPosition))) {
			//outside boundries
			endProgram();
		}
		
		
		snake->add(snake->toIndicies(nextPosition));
		lastCube = snake->toIndicies(nextPosition);
		char buff[256];
		sprintf(buff, "adding cube at %f, %f, %f with current position %f, %f, %f \n", snake->toIndicies(position)[0], snake->toIndicies(position)[1], snake->toIndicies(position)[2], position[0], position[1], position[2]);
		OutputDebugStringA(buff);
		
		if (!snake->isFood(lastCube)) {
			snake->remove();
		}
		else {
			snake->newFood(lastCube);
			moveSpeed *= moveMult;
		
		}
	}
	
	position = nextPosition;

	//baseLookDir = moveDirection;
	if (baseLookDir != moveDirection) {
		baseLookDir = glm::vec3(glm::rotate(baseLookSpeed * glm::angle(baseLookDir, moveDirection), cross(baseLookDir, moveDirection)) * glm::vec4(baseLookDir, 1));
	}
	if (time - lastMouseTime >= 1.f) {
		horizontalAngle -= horizontalAngle * baseLookSnap;
		verticalAngle -= verticalAngle * baseLookSnap;
	}

	lookDir = glm::vec3( glm::rotate(horizontalAngle, lookUp) * glm::rotate(verticalAngle, cross(moveDirection, moveUp))* glm::vec4(baseLookDir,1));
	lookUp = moveUp;


	float FoV = initialFoV;
	float ViewDist = 100.f;
	ProjectionMatrix = glm::perspective(glm::radians(FoV), aspect, 0.1f, ViewDist);
	// Camera matrix

	ViewMatrix = glm::lookAt(
		position,           // Camera is here
		position + lookDir, // and looks here : at the same position, plus "direction"
		lookUp                // Head is up (set to 0,-1,0 to look upside-down)
	);
	lastTime = time;
}*/

/*
glm::mat4 ViewMatrix;
glm::mat4 ProjectionMatrix;

glm::mat4 getViewMatrix() {
	return ViewMatrix;
}
glm::mat4 getProjectionMatrix() {
	return ProjectionMatrix;
}


// Initial position : on +Z
glm::vec3 position = glm::vec3(2, 2, -2);

glm::vec3 moveDirection = glm::vec3(0, 0, -1);
glm::vec3 moveUp = glm::vec3(0, 1, 0);
glm::vec3 baseLookDir = moveDirection;
glm::vec3 LookDir = moveDirection;
// Initial horizontal angle : toward -Z
float horizontalAngle = 3.14f;
// Initial vertical angle : none
float verticalAngle = 0.0f;
// Initial Field of View
float initialFoV = 45.0f;

float speed = 3.0f; // 3 units / second
float mouseSpeed = 0.005f;
double lastMouseTime = glfwGetTime();

static double lastTime = glfwGetTime();

float rotSpeed = 0.05f;
bool mouseMoved = false;


void computeMatricesFromInputs() {

	// glfwGetTime is called only once, the first time this function is called

	// Compute time difference between current and last frame
	double currentTime = glfwGetTime();
	float deltaTime = float(currentTime - lastTime);

	position += moveDirection * speed * deltaTime;

	if (baseLookDir != moveDirection) {
		baseLookDir = glm::vec3(glm::rotate(rotSpeed* angle(baseLookDir, moveDirection), cross(baseLookDir, moveDirection)) * glm::vec4(baseLookDir, 1));
	}

	if (LookDir != baseLookDir && currentTime - lastMouseTime >= 1.0) {
		LookDir = glm::vec3(glm::rotate(rotSpeed* angle(LookDir, baseLookDir), cross(LookDir, baseLookDir)) * glm::vec4(LookDir, 1));
	}

	float FoV = initialFoV;// - 5 * glfwGetMouseWheel(); // Now GLFW 3 requires setting up a callback for this. It's a bit too complicated for this beginner's tutorial, so it's disabled instead.

						   // Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	ProjectionMatrix = glm::perspective(glm::radians(FoV), 4.0f / 3.0f, 0.1f, 100.0f);
	// Camera matrix

	ViewMatrix = glm::lookAt(
		position,           // Camera is here
		position + LookDir, // and looks here : at the same position, plus "direction"
		moveUp                 // Head is up (set to 0,-1,0 to look upside-down)
	);

	// For the next frame, the "last time" will be "now"
	lastTime = currentTime;
}




void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	


	// Move forward
	if (key == GLFW_KEY_W && action == GLFW_PRESS) {
		glm::vec3 temp = invert(moveDirection);
		moveDirection = moveUp;
		moveUp = temp;


	}
	// Move backward
	if (key == GLFW_KEY_S && action == GLFW_PRESS) {
		glm::vec3 temp = invert(moveUp);
		moveUp = moveDirection;
		moveDirection = temp;
	}
	// Strafe right
	if (key == GLFW_KEY_D && action == GLFW_PRESS) {
		moveDirection = cross(moveDirection, moveUp);
	}
	// Strafe left
	if (key == GLFW_KEY_A && action == GLFW_PRESS) {
		moveDirection = invert(cross(moveDirection, moveUp));
	}
}

static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	// Reset mouse position for next frame
	glfwSetCursorPos(window, 1024 / 2, 768 / 2);
	// Direction : Spherical coordinates to Cartesian coordinates conversion
	// Compute new orientation
	horizontalAngle += mouseSpeed * float(1024 / 2 - xpos);
	horizontalAngle = fmod(horizontalAngle, 2 * PI);
	verticalAngle += mouseSpeed * float(768 / 2 - ypos);
	LookDir = glm::vec3(glm::rotate(horizontalAngle, moveUp) * glm::rotate(verticalAngle, cross(baseLookDir, moveUp)) * glm::vec4(baseLookDir,1));
	lastMouseTime = glfwGetTime();
}		
*/
/*
void computeMatricesFromInputs();
glm::mat4 getViewMatrix();
glm::mat4 getProjectionMatrix();
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
*/





#endif