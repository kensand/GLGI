#include "stdafx.h"
#include "GLGI.h"

void GLGI::Object::setScale(glm::vec3 scale) {
	this->ModelScale = scale;
	this->update();
}


glm::vec3 GLGI::Object::getRotation() {
	return glm::vec3(ModelRotation[0], ModelRotation[1], ModelRotation[2]);
}

glm::vec3 GLGI::Object::getPosition() {
	return glm::vec3(ModelLocation[0], ModelLocation[1], ModelLocation[2]);
}

glm::vec3 GLGI::Object::getScale() {
	return this->ModelScale;
}


glm::mat4 GLGI::Object::getModelMatrix() {
	return ModelMatrix;
}

void GLGI::Object::update() {
	glm::mat4 ModelS = glm::scale(this->ModelScale);
	glm::mat4 ModelR = glm::rotate(this->ModelRotation[0], xAxis) * glm::rotate(this->ModelRotation[1], yAxis) *glm::rotate(this->ModelRotation[2], zAxis);
	glm::mat4 ModelT = glm::translate(this->ModelLocation);
	this->ModelMatrix = ModelT * ModelR * ModelS;
}


GLGI::Object::Object() {
	visible = true;
	ModelLocation = glm::vec3(0., 0., 0.);
	ModelScale = glm::vec3(1., 1., 1.);
	ModelRotation = glm::vec3(0., 0., 0.);
	this->update();
	ignoreLights = false;
	mesh = NULL;
	texture = NULL;
	material = NULL;

}

