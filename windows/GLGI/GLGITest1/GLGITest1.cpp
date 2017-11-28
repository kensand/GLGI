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

	GLGI::Object * suzanne = new GLGI::Object();
	GLGI::Camera * cam = new GLGI::Camera();
	suzanne->setMesh(new GLGI::Mesh("suzanne.obj"));
	rm->addResource(suzanne->getMesh());
	scene.addObject(suzanne);
	scene.addCamera(cam);
	scene.update();



	double lastTime = window.getTime();
	int nbFrames = 0;

	/* Loop until the user closes the window */
	while (!window.shouldClose()) {
		renderer.render(&scene);
		scene.update();

		double currentTime = window.getTime();
		nbFrames++;

		
		// Measure speed
		
		if (currentTime - lastTime >= 1.0) { // If last prinf() was more than 1 sec ago
											 // printf and reset timer
			char buff[256];
			printf("%f ms/frame\n", 1000.0 / double(nbFrames));
			DBOUT(buff);
			nbFrames = 0;
			lastTime += 1.0;
		}

	}
	window.close();
	
	return 0;

}

