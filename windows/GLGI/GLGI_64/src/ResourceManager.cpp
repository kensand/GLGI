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
	textureIdArr = NULL;

	for (uint i = 0; i < numResourceTypes; i++) {

		glBindBuffer(GL_ARRAY_BUFFER, vbos[i]);

		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebos[i]);

	}
	this->texdims2D[0] = 1024;
	this->texdims2D[1] = 1024;

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
	return meshStarts[meshStarts.size() - 1];
	//return lastID;

}



GLGI::ResourceId GLGI::ResourceManager::addResource(Texture * texture)
{
	//lastID += 1;
	//textures.push_back(std::pair<ResourceId, Texture*>(lastID, texture));
	//TODO this is inefficient to update each time a resource is added
	textures.push_back(texture);
	
	return 0;// lastID;
}

GLGI::ResourceId GLGI::ResourceManager::addResource(Light * light)
{
	//lastID += 1;
	//textures.push_back(std::pair<ResourceId, Texture*>(lastID, texture));
	//TODO this is inefficient to update each time a resource is added
	lights.push_back(light);

	return 0;// lastID;
}

GLGI::ResourceId GLGI::ResourceManager::addResource(Material * material)
{
	materials.push_back(material);
	return 0;
}

void GLGI::ResourceManager::update() {
	GLint error;

	glBindVertexArray(vaos);
	glBindBuffer(GL_ARRAY_BUFFER, vbos[0]);
	if (vertices.size() >= 0) {
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(PackedVertex), &(vertices[0]), GL_STATIC_DRAW);
	}
	if (textureIdArr != NULL) {
		glDeleteTextures(numTextures, textureIdArr);
		delete[] textureIdArr;
	}
	numTextures = textures.size();
	textureIdArr = new GLuint[numTextures];

	glGenTextures(1, &textures2D);
	glActiveTexture(GL_TEXTURE0);
	if ((error = glGetError()) != GL_NO_ERROR) {
		printf("OPENGL error: %d\n", error);
		error = 0;
	}
	glBindTexture(GL_TEXTURE_2D_ARRAY, textures2D);
	if ((error = glGetError()) != GL_NO_ERROR) {
		printf("OPENGL error: %d\n", error);
		error = 0;
	}

	glTexStorage3D(GL_TEXTURE_2D_ARRAY, 1, GL_RGB8, texdims2D[0], texdims2D[1], numTextures);
	if ((error = glGetError()) != GL_NO_ERROR) {
		printf("OPENGL error: %d\n", error);
		error = 0;
	}
	for (uint i = 0; i < textures.size(); i++) {
		
		
		textureIdArr[i] = i;
		if ((error = glGetError()) != GL_NO_ERROR) {
			printf("OPENGL error: %d\n", error);
			error = 0;
		}
		glTexSubImage3D(GL_TEXTURE_2D_ARRAY, 0,
			0, 0, i, //x, y, z offsets)
			texdims2D[0], texdims2D[1], 1, //x, y, z dimensions
			GL_RGB, GL_UNSIGNED_BYTE, textures[i]->getDataLoc()
		);
		if ((error = glGetError()) != GL_NO_ERROR) {
			printf("OPENGL error: %d\n", error);
			error = 0;
		}
		
	}
	//glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	//glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	//glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_WRAP_T, GL_REPEAT);
	//glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glGenerateMipmap(GL_TEXTURE_2D_ARRAY);
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
	
	if (textureIdArr != NULL) {
		glDeleteTextures(1, &textures2D);
		delete[] textureIdArr;
	}

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

GLuint GLGI::ResourceManager::getTextureUnitId(GLGI::Texture * texture) {
	/*for (unsigned int i = 0; i < textures.size(); i++) {
		if (texture == textures[i]) {
			return textureUnitIds[i];
		}
	}
	throw("Texture id not found");
	return 0;
	*/
	return 0; //TODO this should i where i is GL_TEXTUREi refering to which texture unit(?) is being used.
}

GLuint GLGI::ResourceManager::getTextureId(GLGI::Texture * texture) {
	for (unsigned int i = 0; i < textures.size(); i++) {
		if (texture == textures[i]) {
			return textureIdArr[i];
		}
	}
	throw("Texture uid not found");
	return 0;//TODO this should throw
}

GLuint GLGI::ResourceManager::getMaterialId(Material * material)
{
	for (unsigned int i = 0; i < materials.size(); i++) {
		if (material == materials[i]) {
			return i;
		}
	}
	throw("materialid not found");
	return 0;//TODO this should throw
}
