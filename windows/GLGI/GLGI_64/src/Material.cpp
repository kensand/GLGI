#include "GLGI.h"

GLGI::Material::Material() {
	emission = glm::vec3(1.0, 1.0, 1.0);
	specular = glm::vec3(1.0, 1.0, 1.0);
	ambient = glm::vec3(1.0, 1.0, 1.0);
	diffuse = glm::vec3(1.0, 1.0, 1.0);
	shininess = 16.0;
}
