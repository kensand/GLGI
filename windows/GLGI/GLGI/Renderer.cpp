#include "stdafx.h"
#include "GLGI.h"

GLGI::Renderer::Renderer(ResourceManager * resourceManager, Window * window)
{
	//programID = LoadShaders("StandardShading.vertexshader", "StandardShading.fragmentshader");
	programID = LoadShaders("triangles.vert", "triangles.frag");
	mvpUniform = glGetUniformLocation(programID, "mvpMatrix");
	manager = resourceManager;
	renderWindow = window;
	clearColor = glm::vec4(0.0, 0.0, 1.0, 1.0);
}

void GLGI::Renderer::render(Scene * scene)
{
	scene->update();
	manager->update();//TODO necessary?

	//glEnable(GL_CULL_FACE);
	//glDisable(GL_DEPTH_TEST);
	glm::vec4 black = glm::vec4(0.f, 0.f, 1.f, 1.f);
	glClearBufferfv(GL_COLOR, 0, &(black[0]));
	//glClearColor(clearColor[0], clearColor[1], clearColor[2], clearColor[3]);
	//float temp = clearColor[1];
	//clearColor[1] = clearColor[0];
	//clearColor[0] = temp;
	//glClear(GL_COLOR_BUFFER_BIT);

	// Activate simple shading program
	glUseProgram(programID);

	// Set up for a glDrawElements call
	glBindVertexArray(manager->vaos);

	manager->enableBuffers();



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
	manager->disableBuffers();

	glfwPollEvents();

}

