#pragma once


#include <glm\glm.hpp>
namespace GLGI {
	namespace UTIL {
		template <class S>
		glm::vec3 scalarMultiply(S scalar, glm::vec3 vector) {
			glm::vec3 temp = vector;
			for (uint i = 0; i < 3; i++) {
				temp[i] = vector[i] * scalar;
			}
			return temp;

		}


	}
}
