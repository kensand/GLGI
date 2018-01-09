#include "stdafx.h"
#include "GLGI.h"



GLGI::Mesh::Mesh(const char * path) {
	std::vector<glm::vec3> pos;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;
	loadOBJ(path, pos, uvs, normals);
	for (unsigned int i = 0; i < pos.size(); i++) {
		vertices.push_back(PackedVertex(pos[i], uvs[i], normals[i]));
	}
}

