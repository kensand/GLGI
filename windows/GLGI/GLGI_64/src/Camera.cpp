#include "stdafx.h"
#include "GLGI.h"


GLGI::Camera::Camera()
{
	this->CameraRotation = glm::vec3(0.f, 0.f, 0.f);
	this->CameraLocation = glm::vec3(0.f, 0.f, 0.f);
	this->CameraScale = glm::vec3(1.f, 1.f, 1.f);
	update();
}



void GLGI::Camera::setPosition(GLfloat x, GLfloat y, GLfloat z) {
	this->CameraLocation[0] = x;
	this->CameraLocation[1] = y;
	this->CameraLocation[2] = z;
	this->update();
}


void GLGI::Camera::setPosition(glm::vec3 coords) {
	this->CameraLocation[0] = coords[0];
	this->CameraLocation[1] = coords[1];
	this->CameraLocation[2] = coords[2];
	this->update();
}


void GLGI::Camera::setRotation(GLfloat x, GLfloat y, GLfloat z) {
	//printf("setrotation %f, %f, %f \n", x, y, z);
	this->CameraRotation[0] = x;
	this->CameraRotation[1] = y;
	this->CameraRotation[2] = z;
	this->update();
}


void GLGI::Camera::setRotation(glm::vec3 axisRot) {

	this->CameraRotation[0] = axisRot[0];
	this->CameraRotation[1] = axisRot[1];
	this->CameraRotation[2] = axisRot[2];
	this->update();
}

void GLGI::Camera::setScale(glm::vec3 scale) {
	this->CameraScale = scale;
}


glm::vec3 GLGI::Camera::getRotation() {
	//printf("getrotation %f, %f, %f \n", CameraRotation[0], CameraRotation[1], CameraRotation[2]);
	return  CameraRotation;
}

glm::vec3 GLGI::Camera::getPosition() {
	return glm::vec3(CameraLocation[0], CameraLocation[1], CameraLocation[2]);
}

glm::vec3 GLGI::Camera::getScale() {
	return this->CameraScale;
}

glm::mat4 GLGI::Camera::getRotationMatrix()
{
	return glm::rotate(this->CameraRotation[0], xAxis) * glm::rotate(this->CameraRotation[1], yAxis) *glm::rotate(this->CameraRotation[2], zAxis);
}


glm::mat4 GLGI::Camera::getViewMatrix() {
	return ViewMatrix;
}

void GLGI::Camera::update() {
	float FOV = 45.f;
	//glm::vec3 up = glm::vec3(0., 1., 0.);
	glm::mat4 CameraS = glm::scale(this->CameraScale);
	glm::mat4 CameraR = glm::rotate(this->CameraRotation[0], xAxis) * glm::rotate(this->CameraRotation[1], yAxis) *glm::rotate(this->CameraRotation[2], zAxis);
	glm::mat4 CameraT = glm::translate(glm::vec3( -1 * this->CameraLocation[0],  -1 * this->CameraLocation[1],  -1 * this->CameraLocation[2]));
	this->PerspectiveMatrix = glm::perspective(glm::radians(FOV), 16.0f / 10.0f, 0.1f, 1000.0f);
	this->ViewMatrix = CameraR * CameraT  * CameraS;
	//float a = CameraR[1][2] - CameraR[2][1];
	//float b = CameraR[2][0] - CameraR[0][2];
	//float c = CameraR[0][1] - CameraR[1][0];
	//this->LookDirUnitVec = glm::normalize(glm::vec3(a, b, c));//should the 0 be a 1?
	//glm::mat4 r = glm::rotate(270.f, yAxis);
	glm::vec4 res4 = glm::rotate(-1.f * this->CameraRotation[2], zAxis) * glm::rotate(-1.f * this->CameraRotation[1], yAxis) *glm::rotate(-1.f * this->CameraRotation[0], xAxis) * glm::vec4(0., 0., 1., 1.);
	glm::vec3 res = glm::vec3(res4) / res4[3];

	this->LookDirUnitVec = glm::normalize(res);
	
	//this->ViewMatrix = glm::lookAt(
	//	this->CameraLocation, // Camera is at (4,3,3), in World Space
	//	glm::vec3(glm::vec4(0., 0., -1., 1.) * CameraR), // and looks at the origin
	//	up  // Head is up (set to 0,-1,0 to look upside-down)
	//);
}

glm::mat4 GLGI::Camera::getPerspectiveMatrix() {
	return this->PerspectiveMatrix;
}

glm::vec3 GLGI::Camera::getLookDirUnitVec() {

	return this->LookDirUnitVec;
}