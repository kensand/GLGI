// GLGITest1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Windows.h>
//#include "../GLGI_64/GLGI.h"
#include <GLGI.h>

#define DEBUG DEBUG
#ifdef DEBUG
#define _CRTDBG_MAP_ALLOC true
#include <stdlib.h>
#include <crtdbg.h>
#endif // DEBUG


#include <sstream>
#define DBOUT( s )            \
{                             \
   std::ostringstream os_;    \
   os_ << s;                   \
   OutputDebugStringA( os_.str().c_str() );  \
}\







int main()
{

#ifdef DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	const char * vert = "resources/shaders/simple.vert";
	const char * frag = "resources/shaders/simple.frag";

	GLGI::Window window;
	GLGI::ResourceManager * rm = new GLGI::ResourceManager();
	GLGI::Renderer renderer(rm, &window, vert, frag);
	GLGI::Scene scene;


	GLGI::Light l = GLGI::Light();
	l.local = true;
	l.spot = true;
	l.coneDirection = glm::vec3(0., -1., 0.);
	l.spotCosCutoff = 0.01;
	//l.ambient = glm::vec3(0.5, 0.5, 0.5);
	l.ambient = glm::vec3(0., 0., 0.);
	l.color = glm::vec3(1., 1., 1.);
	//l.color = glm::vec3(0., 0., 0.);
	l.position = glm::vec3(0., 10., -10.);
	l.linearAttenuation = 0.01; //0.001
	l.quadraticAttenuation = 0.001; //0.00001
	l.constantAttenuation = 1.;
	rm->addResource(&l);

	GLGI::Light l2 = GLGI::Light();
	//l2.local = true;
	//l2.spot = true;
	l2.coneDirection = glm::vec3(0., -1., 0.);
	l2.spotCosCutoff = 0.01;
	//l.ambient = glm::vec3(0.5, 0.5, 0.5);
	l2.ambient = glm::vec3(0., 0., 0.);
	//l2.color = glm::vec3(1., 1., 1.);
	l2.color = glm::vec3(0.1, 0.1, 0.1);
	l2.position = glm::vec3(0, 10., 10.);
	l2.linearAttenuation = 0.01; //0.001
	l2.quadraticAttenuation = 0.001; //0.00001
	l2.constantAttenuation = 1.;
	rm->addResource(&l2);

	
	
	printf("vertexSize = %d\n", sizeof(GLGI::PackedVertex));
	printf("vec3size = %d\n", sizeof(glm::vec3));
	printf("vec2size = %d\n", sizeof(glm::vec2));
	printf("GLfloatsize = %d\n", sizeof(GL_FLOAT));

	//GLGI::Object * suzanne = new GLGI::Object();
	//GLGI::Object * suzanne2 = new GLGI::Object();
	GLGI::Camera * cam = new GLGI::Camera();
	cam->setPosition(0., 0., 0.);
	cam->setRotation(0., 0., 0.);


	

	GLGI::Mesh * mesh1 = new GLGI::Mesh("resources/sphere.obj", glm::vec4(1.f, 1.f, 0.f, 0.2f));
	GLGI::Mesh * mesh2 = new GLGI::Mesh("resources/cube2.obj", glm::vec4(1.f, 1.f, 1.f, 1.f));
	//GLGI::Mesh * mesh1 = new GLGI::Mesh("capsule.obj", glm::vec4(0.f, 1.f, 0.f, 0.f));
	//GLGI::Mesh * mesh2 = new GLGI::Mesh("capsule.obj", glm::vec4(1.f, 0.f, 0.f, 1.f));
	//GLGI::Texture * tex2 = new GLGI::Texture("capsule.png");
	//GLGI::Texture * tex1 = new GLGI::Texture("capsule.png");
	GLGI::Texture * tex1 = new GLGI::Texture("resources/test1.jpg");
	GLGI::Texture * tex2 = new GLGI::Texture("resources/cube2.jpg");
	GLGI::Material * mat1 = new GLGI::Material();
	//mat1->shininess = 1.;


	

	//GLGI::Texture * tex2 = new GLGI::Texture("capsule.jpg");
	//GLGI::Texture * tex1 = new GLGI::Texture("capsule.jpg");

	//GLGI::Texture * tex1 = new GLGI::Texture("test1.jpg");

	//GLGI::Texture * tex2 = new GLGI::Texture("test2.jpg");
	rm->addResource(mesh1);
	rm->addResource(mesh2);
	rm->addResource(tex1);
	rm->addResource(tex2);
	rm->addResource(mat1);

	for (int i = 0; i < 50; i++) {
		GLGI::Object * obj = new GLGI::Object();
		obj->setPosition(-100. + 4. *i, 0., -2.);
		obj->setMesh(i % 2 == 0 ? mesh1 : mesh2);
		//obj->setMesh(mesh2);
		obj->setTexture(i % 2 == 0 ? tex1 : tex2);
		obj->setMaterial(mat1);
		scene.addObject(obj);
	}

	GLGI::Object * obj = new GLGI::Object();
	obj->setPosition(0., -10., 0.);
	obj->setMesh(mesh2);
	//obj->setMesh(mesh2);
	obj->setTexture(NULL);
	obj->setScale(glm::vec3(100., .1, 100.));
	obj->setMaterial(mat1);
	scene.addObject(obj);

	GLGI::Object * sun = new GLGI::Object();
	sun->setPosition(l.position);
	sun->setMesh(mesh1);
	sun->setIgnoreLight(true);
	sun->setMaterial(mat1);
	scene.addObject(sun);

	GLGI::Object * sun2 = new GLGI::Object();
	sun2->setPosition(l2.position);
	sun2->setMesh(mesh1);
	sun2->setIgnoreLight(true);
	sun2->setMaterial(mat1);
	scene.addObject(sun2);

	//rm->update();

	//suzanne->setPosition(-10., 0., -2.0);
	//suzanne2->setPosition(0., 0., -1.0);
	//suzanne2->setMesh(new GLGI::Mesh("suzanne.obj", glm::vec4(0.f, 1.f, 0.f, 1.f)));
	//suzanne2->setMesh(new GLGI::Mesh("triangle.obj"));
	//suzanne->setMesh(new GLGI::Mesh("cube.obj", glm::vec4(1.f, 0.f, 0.f, 1.f)));
	//suzanne->setMesh(new GLGI::Mesh("cube.obj"));

	//rm->addResource(suzanne->getMesh());
	//rm->addResource(suzanne2->getMesh());
	
	//scene.addObject(suzanne);
	//scene.addObject(suzanne2);
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
	rm->update();
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
		l.position[0] = sin((float) currentTime ) * 100.f ;
		l2.position[0] = cos((float)currentTime ) * 100.f;
		sun->setPosition(l.position);
		sun2->setPosition(l2.position);
		lastFrameTime = currentTime;
		

		lastMouseX = window.getMouseX();
		lastMouseY = window.getMouseY();

		

		
		// Measure speed
		
		if (currentTime - lastTime >= 1.0) { // If last prinf() was more than 1 sec ago
											 // printf and reset timer
			printf("%f ms/frame\n", 1000.0 / double(nbFrames));
			nbFrames = 0;
			lastTime = currentTime;
		}


	}
	window.close();
	
	delete tex1;
	delete tex2;
	//delete suzanne;
	//delete suzanne2;
	delete cam;
	for (uint i = 0; i < scene.objects.size(); i++) {
		delete scene.objects[i];
	}
	delete mesh1;
	delete mesh2;
	delete mat1;
	delete rm;


	
	
	return 0;

}

