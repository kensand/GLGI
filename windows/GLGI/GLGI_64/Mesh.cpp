#include "stdafx.h"
#include "GLGI.h"
#include <iostream>



GLGI::Mesh::Mesh(const char * path, glm::vec4 color) {
	std::vector<glm::vec3> pos;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;


	
	tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;

	std::string err;
	bool ret = tinyobj::LoadObj(&attrib, &shapes, &materials, &err, path);

	if (!err.empty()) { // `err` may contain warning message.
		std::cerr << err << std::endl;
	}

	
	loadOBJ(path, pos, uvs, normals);
	for (unsigned int i = 0; i < pos.size(); i++) {
		vertices.push_back(PackedVertex(pos[i], uvs[i], normals[i], color));
	}
}

