// GLGITest1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Windows.h>
#include "../GLGI/GLGI.h"


#include <sstream>
#define DBOUT( s )            \
{                             \
   std::ostringstream os_;    \
   os_ << s;                   \
   OutputDebugStringA( os_.str().c_str() );  \
}\




int main()
{
	GLGI::Window window;
	GLGI::ResourceManager * rm = new GLGI::ResourceManager();
	GLGI::Renderer renderer(rm, &window);
	GLGI::Scene scene;

	printf("vertexSize = %d\n", sizeof(GLGI::PackedVertex));
	printf("vec3size = %d\n", sizeof(glm::vec3));
	printf("vec2size = %d\n", sizeof(glm::vec2));
	printf("GLfloatsize = %d\n", sizeof(GL_FLOAT));

	GLGI::Object * suzanne = new GLGI::Object();
	GLGI::Object * suzanne2 = new GLGI::Object();
	GLGI::Camera * cam = new GLGI::Camera();
	cam->setPosition(0., 0., 0.);
	cam->setRotation(0., 0., 0.);
	suzanne->setPosition(-80., 0., -2.0);
	suzanne2->setPosition(0., 0., -1.0);
	suzanne2->setMesh(new GLGI::Mesh("suzanne.obj"));
	//suzanne2->setMesh(new GLGI::Mesh("triangle.obj"));
	//suzanne2->setMesh(new GLGI::Mesh("square.obj"));
	suzanne->setMesh(new GLGI::Mesh("cube.obj"));
	rm->addResource(suzanne->getMesh());
	rm->addResource(suzanne2->getMesh());
	//scene.addObject(suzanne);
	scene.addObject(suzanne2);
	scene.addCamera(cam);
	window.makeCurrentWindow();
	


	double speed = 0.5;
	double mouseSpeed = 0.005;
	double lastTime = window.getTime();
	double lastFrameTime = window.getTime();
	int nbFrames = 0;
	double lastMouseX = window.getMouseX();
	double lastMouseY = window.getMouseY();
	/* Loop until the user closes the window */
	while (!window.shouldClose()) {
		double currentTime = window.getTime();
		nbFrames++;

		renderer.render(&scene);

		glm::vec3 rot = cam->getRotation();
		//printf("between 1 %f, %f, %f \n", rot.x, rot.y, rot.z);
		rot.y = rot.y + mouseSpeed * (window.getMouseX() - lastMouseX);
		rot.x = rot.x + mouseSpeed * (window.getMouseY() - lastMouseY);
		//printf("between 2 %f, %f, %f \n", rot.x, rot.y, rot.z);
		cam->setRotation(rot.x, rot.y, rot.z);
		if (window.getKey(GLFW_KEY_W) == GLFW_PRESS) {
			glm::vec3 oldpos = cam->getPosition();
			oldpos[2] -= speed *(currentTime - lastFrameTime);
			cam->setPosition(oldpos);
		}
		if (window.getKey(GLFW_KEY_A) == GLFW_PRESS) {
			glm::vec3 oldpos = cam->getPosition();
			oldpos[0] -= speed *(currentTime - lastFrameTime);
			cam->setPosition(oldpos);
		}
		if (window.getKey(GLFW_KEY_S) == GLFW_PRESS) {
			glm::vec3 oldpos = cam->getPosition();
			oldpos[2] += speed *(currentTime - lastFrameTime);
			cam->setPosition(oldpos);
		}
		if (window.getKey(GLFW_KEY_D) == GLFW_PRESS) {
			glm::vec3 oldpos = cam->getPosition();
			oldpos[0] += speed *(currentTime - lastFrameTime);
			cam->setPosition(oldpos);
		}
		lastFrameTime = currentTime;
		

		lastMouseX = window.getMouseX();
		lastMouseY = window.getMouseY();

		

		
		// Measure speed
		
		if (currentTime - lastTime >= 1.0) { // If last prinf() was more than 1 sec ago
											 // printf and reset timer
			char buff[256];
			printf("%f ms/frame\n", 1000.0 / double(nbFrames));
			nbFrames = 0;
			lastTime = currentTime;
		}


	}
	window.close();
	
	return 0;

}

