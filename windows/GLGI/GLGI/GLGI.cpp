// GLGI.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "GLGI.h"




// This is an example of an exported variable
GLGI_API int nGLGI=0;

// This is an example of an exported function.
GLGI_API int fnGLGI(void)
{
	return 42;
}




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
	
	
	glGenBuffers(1, &(vbos[0]));
	
	
	
	//glGenBuffers(numResourceTypes, ebos);
	for (int i = 0; i < numResourceTypes; i++) {

		glBindBuffer(GL_ARRAY_BUFFER, vbos[i]);
		
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebos[i]);

	}


	glGenVertexArrays(1, &vaos);
	glBindVertexArray(vaos);

}

GLGI::ResourceId GLGI::ResourceManager::addResource(Mesh * mesh)
{
	//lastID += 1;
	meshStarts.push_back(vertices.size());
	meshes.push_back(mesh);
	for (int i = 0; i < meshes.size(); i++) {
		for (int j = 0; j < meshes[i]->size(); j++) {
			vertices.push_back((*meshes[i])[j]);
		}
	}
	return meshStarts[meshStarts.size() - 1];
	//return lastID;
}

GLGI::ResourceId GLGI::ResourceManager::addResource(Texture * texture)
{
	//lastID += 1;
	//textures.push_back(std::pair<ResourceId, Texture*>(lastID, texture));
	return 0;// lastID;
}

void GLGI::ResourceManager::update()
{
	
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(PackedVertex), &(vertices[0]), GL_STATIC_DRAW);

	/*
	position vertex attribute:
	index: positions enum
	size: 3 (glm::vec3)
	type: GLfloat
	normalized: no
	stride: size of uv + size of normal
	pointer: 0 - start at beginning of vbo
	*/
	glVertexAttribPointer(positions, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec2) + sizeof(glm::vec3), 0);

	/*
	uvs vertex attribute:
	index: positions enum
	size: 2 (glm::vec2)
	type: GLfloat
	normalized: no
	stride: size of position + size of normal
	pointer: sizeof(vec3) - start after the first position vector
	*/
	glVertexAttribPointer(uvs, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(glm::vec3), (const void *) sizeof(glm::vec3));

	/*
	normals vertex attribute:
	index: positions enum
	size: 3 (glm::vec3)
	type: GLfloat
	normalized: no
	stride: size of uv + size of position
	pointer: size of uv + size of position - start after other 2 attributes
	*/
	glVertexAttribPointer(normals, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec2) + sizeof(glm::vec3), (const void *)(sizeof(glm::vec2) + sizeof(glm::vec3)));
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(meshes), &(meshes[0]), GL_STATIC_DRAW);
}

GLGI::ResourceManager::~ResourceManager() {
	
	glDeleteBuffers(numResourceTypes, vbos);
	glDeleteBuffers(numResourceTypes, ebos);

}

void GLGI::Scene::update() {

}





// This is the constructor of a class that has been exported.
// see GLGI.h for the class definition
GLGI::Window::Window()
{
	if (!glfwInit())
		throw("GLFW init Failure");

	/* Create a windowed mode window and its OpenGL context */
	glfwwindow = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	if (!glfwwindow)
	{
		glfwTerminate();
		throw("GLFW window creation failed;");
	}

	makeCurrentContext();

	glewExperimental = GL_TRUE;
	if (glewInit()) {
		DBOUT("glew init Failure");
		throw("glew init Failure");
	}
    return;
}
bool GLGI::Window::shouldClose() {
	return glfwWindowShouldClose(glfwwindow);
}

void GLGI::Window::close() {
	glfwTerminate();
}
void GLGI::Window::makeCurrentContext() {
	glfwMakeContextCurrent(glfwwindow);
}

void GLGI::Window::draw() {
	/* Render here */
	glClear(GL_COLOR_BUFFER_BIT);

	/* Swap front and back buffers */
	glfwSwapBuffers(glfwwindow);

	/* Poll for and process events */
	glfwPollEvents();
}

template <typename T>
void GLGI::Object::setPosition(T x, T y, T z) {
	this->ModelLocation[0] = (GLfloat)x;
	this->ModelLocation[1] = (GLfloat)y;
	this->ModelLocation[2] = (GLfloat)z;
	this->update();
}

template <typename T>
void GLGI::Object::setPosition(T coords) {
	this->ModelLocation[0] = (GLfloat)coords[0];
	this->ModelLocation[1] = (GLfloat)coords[1];
	this->ModelLocation[2] = (GLfloat)coords[2];
	this->update();
}

template <typename T>
void GLGI::Object::setRotation(T x, T y, T z) {
	this->ModelRotation[0] = (GLfloat)x;
	this->ModelRotation[1] = (GLfloat)y;
	this->ModelRotation[2] = (GLfloat)z;
	this->update();
}

template <typename T>
void GLGI::Object::setRotation(T axisRot) {
	this->ModelRotation[0] = (GLfloat)axisRot[0];
	this->ModelRotation[1] = (GLfloat)axisRot[1];
	this->ModelRotation[2] = (GLfloat)axisRot[2];
	this->update();
}
void GLGI::Object::setScale(glm::vec3 scale) {
	this->ModelScale = scale;
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
	glm::mat4 ModelT = glm::translate(glm::vec3(this->ModelLocation[0], this->ModelLocation[1], this->ModelLocation[2]));
	this->ModelMatrix = ModelT * ModelR * ModelS;
}


GLGI::Object::Object() {
	visible = true;
}



template <typename T>
void GLGI::Camera::setPosition(T x, T y, T z) {
	this->CameraLocation[0] = (GLfloat)x;
	this->CameraLocation[1] = (GLfloat)y;
	this->CameraLocation[2] = (GLfloat)z;
	this->update();
}

template <typename T>
void GLGI::Camera::setPosition(T coords) {
	this->CameraLocation[0] = (GLfloat)coords[0];
	this->CameraLocation[1] = (GLfloat)coords[1];
	this->CameraLocation[2] = (GLfloat)coords[2];
	this->update();
}

template <typename T>
void GLGI::Camera::setRotation(T x, T y, T z) {
	this->CameraRotation[0] = (GLfloat)x;
	this->CameraRotation[1] = (GLfloat)y;
	this->CameraRotation[2] = (GLfloat)z;
	this->update();
}

template <typename T>
void GLGI::Camera::setRotation(T axisRot) {
	this->CameraRotation[0] = (GLfloat)axisRot[0];
	this->CameraRotation[1] = (GLfloat)axisRot[1];
	this->CameraRotation[2] = (GLfloat)axisRot[2];
	this->update();
}
GLGI::Camera::Camera()
{
	update();
}
void GLGI::Camera::setScale(glm::vec3 scale) {
	this->CameraScale = scale;
}


glm::vec3 GLGI::Camera::getRotation() {
	return glm::vec3(CameraRotation[0], CameraRotation[1], CameraRotation[2]);
}

glm::vec3 GLGI::Camera::getPosition() {
	return glm::vec3(CameraLocation[0], CameraLocation[1], CameraLocation[2]);
}

glm::vec3 GLGI::Camera::getScale() {
	return this->CameraScale;
}


glm::mat4 GLGI::Camera::getViewMatrix() {
	return ViewMatrix;
}

void GLGI::Camera::update() {
	float FOV = 45.f;
	glm::mat4 CameraS = glm::scale(this->CameraScale);
	glm::mat4 CameraR = glm::rotate(this->CameraRotation[0], xAxis) * glm::rotate(this->CameraRotation[1], yAxis) *glm::rotate(this->CameraRotation[2], zAxis);
	glm::mat4 CameraT = glm::translate(glm::vec3(this->CameraLocation[0], this->CameraLocation[1], this->CameraLocation[2]));
	this->PerspectiveMatrix = glm::perspective(glm::radians(FOV), 4.0f / 3.0f, 0.1f, 100.0f);
	this->ViewMatrix = CameraT * CameraR * CameraS;
}

glm::mat4 GLGI::Camera::getPerspectiveMatrix() {
	return this->PerspectiveMatrix;
}

GLGI::Mesh::Mesh(const char * path) {
	std::vector<glm::vec3> pos;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;
	loadOBJ(path, pos, uvs, normals);
	for (unsigned int i = 0; i < vertices.size(); i++) {
		vertices.push_back(PackedVertex(pos[i], uvs[i], normals[i]));
	}
}


GLGI::PackedVertex::PackedVertex(glm::vec3 Position, glm::vec2 UV, glm::vec3 Normal)
{
	
	glm::vec3 position = Position;
	glm::vec2 uv = UV;
	glm::vec3 normal = Normal;
	
}

GLGI::PackedVertex::PackedVertex(const PackedVertex & copy)
{
	glm::vec3 position = copy.position;
	glm::vec2 uv = copy.uv;
	glm::vec3 normal = copy.normal;

}


bool GLGI::PackedVertex::operator<(const PackedVertex that) const {
	return memcmp((void*)this, (void*)&that, sizeof(PackedVertex))>0;
};

GLGI::Renderer::Renderer(ResourceManager * resourceManager, Window * window)
{
	programID = LoadShaders("StandardShading.vertexshader", "StandardShading.fragmentshader");
	mvpUniform = glGetUniformLocation(programID, "mvpMatrix");
	manager = resourceManager;
	renderWindow = window;
}

void GLGI::Renderer::render(Scene * scene)
{
	glEnable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);
	glm::vec4 black = glm::vec4(0.f, 0.f, 1.f, 1.f);
	glClearBufferfv(GL_COLOR, 0, &(black[0]));

	// Activate simple shading program
	glUseProgram(programID);

	// Set up for a glDrawElements call
	glBindVertexArray(manager->vaos);

	// Set up the model and projection matrix
	glm::mat4 perspective = scene->currentCamera->getPerspectiveMatrix();
	glm::mat4 view = scene->currentCamera->getViewMatrix();
	glm::mat4 vp = perspective * view;
	for (unsigned int i = 0; i < scene->objects.size(); i++) {
		if (scene->objects[i]->isVisible()) {
			glm::mat4 mvp = vp * scene->objects[i]->getModelMatrix();
			glUniformMatrix4fv(mvpUniform, 1, GL_FALSE, &(mvp[0][0]));
			GLuint start = manager->getMeshStart(scene->objects[i]->getMesh());
			GLuint size = scene->objects[i]->getMesh()->size();
			glDrawArrays(GL_TRIANGLES, start, size);
		}
	}
	glfwSwapBuffers(renderWindow->glfwwindow);
	glfwPollEvents();

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
