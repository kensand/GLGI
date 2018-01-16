#include "stdafx.h"
#include "GLGI.h"



/*
bool getSimilarVertexIndex_fast(
GLGI::PackedVertex & packed,
std::map<GLGI::PackedVertex, unsigned short> & VertexToOutIndex,
unsigned short & result
) {
std::map<GLGI::PackedVertex, unsigned short>::iterator it = VertexToOutIndex.find(packed);
if (it == VertexToOutIndex.end()) {
return false;
}
else {
result = it->second;
return true;
}
}

void indexVBO(
std::vector<GLGI::Mesh> & meshes,

std::vector<unsigned short> & out_indices,
std::vector<GLGI::Mesh> & out_meshes
) {
std::map<GLGI::PackedVertex, unsigned short> VertexToOutIndex;

// For each input vertex
for (unsigned int i = 0; i<meshes.size(); i++) {
for (unsigned int j = 0; j<meshes[i].size(); j++) {
GLGI::PackedVertex packed = meshes[i][j];


// Try to find a similar vertex in out_XXXX
unsigned short index;
bool found = getSimilarVertexIndex_fast(packed, VertexToOutIndex, index);

if (found) { // A similar vertex is already in the VBO, use it instead !
out_indices.push_back(index);
}
else { // If not, it needs to be added in the output data.

out_meshes.push_back(meshes[i])

out_vertices.push_back(in_vertices[i]);
out_uvs.push_back(in_uvs[i]);
out_normals.push_back(in_normals[i]);
unsigned short newindex = (unsigned short)out_vertices.size() - 1;
out_indices.push_back(newindex);
VertexToOutIndex[packed] = newindex;
}
}
}

*/
GLGI::ResourceManager::ResourceManager() {


	
	


	//glGenBuffers(numResourceTypes, ebos);
	


	glGenVertexArrays(1, &vaos);
	glBindVertexArray(vaos);
	glGenBuffers(1, &(vbos[0]));

	for (uint i = 0; i < numResourceTypes; i++) {

		glBindBuffer(GL_ARRAY_BUFFER, vbos[i]);

		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebos[i]);

	}

}

GLGI::ResourceId GLGI::ResourceManager::addResource(Mesh * mesh)
{
	//lastID += 1;
	meshStarts.push_back(vertices.size());
	meshes.push_back(mesh);
	
	for (uint j = 0; j < mesh->size(); j++) {
			vertices.push_back((*mesh)[j]);
	}

	//TODO this is inefficient to update each time a resource is added
	this->update();
	return meshStarts[meshStarts.size() - 1];
	//return lastID;

}

GLGI::ResourceId GLGI::ResourceManager::addResource(Texture * texture)
{
	//lastID += 1;
	//textures.push_back(std::pair<ResourceId, Texture*>(lastID, texture));
	//TODO this is inefficient to update each time a resource is added
	this->update();
	return 0;// lastID;
}

void GLGI::ResourceManager::update() {

	glBindVertexArray(vaos);
	glBindBuffer(GL_ARRAY_BUFFER, vbos[0]);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(PackedVertex), &(vertices[0]), GL_STATIC_DRAW);

}

void GLGI::ResourceManager::disableBuffers() {

	glDisableVertexAttribArray(positions);
	glDisableVertexAttribArray(normals);
	glDisableVertexAttribArray(colors);
	glDisableVertexAttribArray(uvs);

}

void GLGI::ResourceManager::enableBuffers()
{

	glBindVertexArray(vaos);
	glBindBuffer(GL_ARRAY_BUFFER, vbos[0]);
	glEnableVertexAttribArray(positions);
	glEnableVertexAttribArray(normals);
	glEnableVertexAttribArray(colors);
	glEnableVertexAttribArray(uvs);
	//glEnableVertexAttribArray(vaos);
	/*
	position vertex attribute:
	index: positions enum
	size: 3 (glm::vec3)
	type: GLfloat
	normalized: no
	stride: size of uv + size of normal
	pointer: 0 - start at beginning of vbo
	*/
	glVertexAttribPointer(positions, 3, GL_FLOAT, GL_FALSE, sizeof(PackedVertex), (const void *)0);
	//glEnableVertexAttribArray(positions);
	/*
	normals vertex attribute:
	index: positions enum
	size: 3 (glm::vec3)
	type: GLfloat
	normalized: no
	stride: size of uv + size of position
	pointer: size of uv + size of position - start after other 2 attributes
	*/
	glVertexAttribPointer(normals, 3, GL_FLOAT, GL_FALSE, sizeof(PackedVertex), (const void *)sizeof(glm::vec3));

	//glEnableVertexAttribArray(normals);

	glVertexAttribPointer(colors, 4, GL_FLOAT, GL_FALSE, sizeof(PackedVertex), (const void *)(2 * sizeof(glm::vec3)));
	/*
	uvs vertex attribute:
	index: positions enum
	size: 2 (glm::vec2)
	type: GLfloat
	normalized: no
	stride: size of position + size of normal
	pointer: sizeof(vec3) - start after the first position vector
	*/
	glVertexAttribPointer(uvs, 2, GL_FLOAT, GL_FALSE, sizeof(PackedVertex), (const void *) (sizeof(glm::vec4) + 2 * sizeof(glm::vec3)));
	//glEnableVertexAttribArray(uvs);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(meshes), &(meshes[0]), GL_STATIC_DRAW);
}

GLGI::ResourceManager::~ResourceManager() {

	glDeleteBuffers(numResourceTypes, vbos);
	//glDeleteBuffers(numResourceTypes, ebos);

}


GLuint GLGI::ResourceManager::getMeshStart(Mesh * mesh)
{
	for (unsigned int i = 0; i < meshes.size(); i++) {
		if (mesh == meshes[i]) {
			return meshStarts[i];
		}
	}
	return 0;//TODO this should throw
}
