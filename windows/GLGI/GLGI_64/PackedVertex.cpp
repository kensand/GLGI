#include "stdafx.h"
#include "GLGI.h"


GLGI::PackedVertex::PackedVertex(glm::vec3 Position, glm::vec2 UV, glm::vec3 Normal, glm::vec4 Color)
{

	position = Position;
	uv = UV;
	color = Color;
	normal = Normal;

}

GLGI::PackedVertex::PackedVertex(const PackedVertex & copy)
{
	position = copy.position;
	uv = copy.uv;
	normal = copy.normal;
	color = copy.color;

}


bool GLGI::PackedVertex::operator<(const PackedVertex that) const {
	return memcmp((void*)this, (void*)&that, sizeof(PackedVertex))>0;
};

