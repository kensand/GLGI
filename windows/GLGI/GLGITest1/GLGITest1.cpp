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
	suzanne->setMesh(new GLGI::Mesh("square.obj"));
	//suzanne->setMesh(new GLGI::Mesh("cube.obj"));
	
	rm->addResource(suzanne2->getMesh());
	rm->addResource(suzanne->getMesh());
	scene.addObject(suzanne);
	scene.addObject(suzanne2);
	scene.addCamera(cam);
	window.makeCurrentWindow();
	
	

	/*GLGI::InputManager::KeyFuncType Forward_W = [](int key, int state, int mods) {
		if (key == GLGI_KEY_W && state == GLGI_PRESS) {
			glm::vec3 oldpos = cam->getPosition();
			oldpos[2] -= speed *(currentTime - lastFrameTime);
			cam->setPosition(oldpos);
		}
	}
	*/
	double rotSpeed = 0.001;
	double moveSpeed = 0.001;
	GLGI::CamMove cf = GLGI::CamMove(GLGI_KEY_W, cam, moveSpeed, GLGI::zAxis);
	GLGI::CamMove cb = GLGI::CamMove(GLGI_KEY_S, cam, moveSpeed, glm::vec3(0,0,1));
	GLGI::CamMove cl = GLGI::CamMove(GLGI_KEY_D, cam, moveSpeed, GLGI::xAxis);
	GLGI::CamMove cr = GLGI::CamMove(GLGI_KEY_A, cam, moveSpeed, glm::vec3(-1, 0, 0));
	GLGI::CamRotate rot(&window, cam, rotSpeed);
	GLGI::MouseToggle mt(&window, GLGI_KEY_ESCAPE, window.getInputManager(), &rot, GLGI_CURSOR_DISABLED, GLGI_CURSOR_NORMAL);

	GLGI::InputManager * im = window.getInputManager();
	im->addKeyFunction(GLGI_KEY_W, &cf);
	im->addKeyFunction(GLGI_KEY_S, &cb);
	im->addKeyFunction(GLGI_KEY_D, &cl);
	im->addKeyFunction(GLGI_KEY_A, &cr);
	im->addMousePosFunction(&rot);
	im->addKeyFunction(GLGI_KEY_ESCAPE, &mt);
	

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
		/*
		glm::vec3 rot = cam->getRotation();
		//printf("between 1 %f, %f, %f \n", rot.x, rot.y, rot.z);
		rot.y = rot.y + mouseSpeed * (window.getMouseX() - lastMouseX);
		rot.x = rot.x + mouseSpeed * (window.getMouseY() - lastMouseY);
		//printf("between 2 %f, %f, %f \n", rot.x, rot.y, rot.z);
		cam->setRotation(rot.x, rot.y, rot.z);
		/*if (window.getKey(GLFW_KEY_W) == GLFW_PRESS) {
			glm::vec3 oldpos = cam->getPosition();
			oldpos[2] -= speed *(currentTime - lastFrameTime);
			cam->setPosition(oldpos);
		}*/
		
		cf.update();
		cb.update();
		cl.update();
		cr.update();
		
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

