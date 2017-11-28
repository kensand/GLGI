#include "stdafx.h"
#include "GLGI.h"
GLGI::Scene::Scene() {

}
void GLGI::Scene::addObject(Object * o) {
	this->objects.push_back(o);
}
void GLGI::Scene::addCamera(Camera * c) {
	if (cameras.size() == 0) {
		currentCamera = c;
	}
	this->cameras.push_back(c);
	
}