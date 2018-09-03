#include "GLGI.h"

GLGI::Light::Light() {
	enabled = true;
	local = false; //true;
	spot = false; //true;
	ambient = glm::vec3(0.1, 0.1, 0.1);
	color = glm::vec3(1.0, 1.0, 1.0);
	position = glm::vec3(0., 0., 0.);
	halfVector = glm::vec3(0., -1., 0.);
	coneDirection = glm::vec3(0., -1., 0.);

	spotCosCutoff = .01;
	spotExponent = 2.;
	constantAttenuation = 1.;
	linearAttenuation = 0.1;
	quadraticAttenuation = 0.1;
	calcPosition = position;
	
}
