#include <string>
#include "GLGI.h"


GLGI::Renderer::Renderer(ResourceManager * resourceManager, Window * window, const char * vertexshaderpath, const char * fragmentshaderpath, const char * vertexshadowshaderpath, const char * fragmentshadowshaderpath)
{
	programID = LoadShaders(vertexshaderpath, fragmentshaderpath);
        if (vertexshadowshaderpath != NULL && fragmentshadowshaderpath != NULL) {
                shadowProgramID = LoadShaders(vertexshadowshaderpath, fragmentshadowshaderpath);
        }
	else{
		shadowProgramID = NULL;
	}
        glGenFramebuffers(1, &shadowfbo);
        glGenTextures(1, &shadowTexturesCubeMap);
        glActiveTexture(GL_TEXTURE1);
        GLint error;
        if ((error = glGetError()) != GL_NO_ERROR) {
                printf("OPENGL error: %d\n", error);
                error = GL_NO_ERROR;
        }
        glBindTexture(GL_TEXTURE_CUBE_MAP_ARRAY, shadowTexturesCubeMap);
        if ((error = glGetError()) != GL_NO_ERROR) {
                printf("OPENGL error: %d\n", error);
                error = GL_NO_ERROR;
        }

        glTexImage3D(GL_TEXTURE_CUBE_MAP_ARRAY, 1, GL_DEPTH_COMPONENT, 1024, 1024, maxlights * 6, 0, GL_DEPTH_COMPONENT, GL_DEPTH_COMPONENT16, (void*) NULL);
        if ((error = glGetError()) != GL_NO_ERROR) {
                printf("OPENGL error: %d\n", error);
                error = GL_NO_ERROR;
        }
        glBindTexture(GL_TEXTURE_CUBE_MAP_ARRAY, 1);




	//programID = LoadShaders("StandardShading.vertexshader", "StandardShading.fragmentshader");



	mvpUniform = glGetUniformLocation(programID, "mvpMatrix");
	if (mvpUniform < 0) {
		printf("GL shader ERROR: mvp matrix uniform not found\n");
	}

	mvUniform = glGetUniformLocation(programID, "mvMatrix");
	if (mvUniform < 0) {
		printf("GL shader ERROR: mv matrix uniform not found\n");
	}

	mUniform = glGetUniformLocation(programID, "mMatrix");
	if (mUniform < 0) {
		printf("GL shader ERROR: m matrix uniform not found\n");
	}

	eyeUniform = glGetUniformLocation(programID, "EyeDirection");
	if (eyeUniform < 0) {
		printf("GL shader ERROR: eye uniform not found\n");
	}

	texUniform = glGetUniformLocation(programID, "textureData");
	if (texUniform < 0) {
		printf("GL shader ERROR: texture uniform not found\n");
	}

	texIDUniform = glGetUniformLocation(programID, "textureID");
	if (texIDUniform < 0) {
		printf("GL shader ERROR: texID uniform not found\n");
	}

	materialIndexUniform = glGetUniformLocation(programID, "materialIndex");
	if (materialIndexUniform < 0) {
		printf("GL shader ERROR: MaterialIndex uniform not found\n");
	}

	numLightsUniform = glGetUniformLocation(programID, "numLights");
	if (numLightsUniform < 0) {
		printf("GL shader ERROR: numLights uniform not found\n");
	}
	/*
	ambientUniform = glGetUniformLocation(programID, "Ambient");
	if (ambientUniform < 0) {
		printf("GL shader ERROR: ambient uniform not found");
	}
	*/
	manager = resourceManager;
	
	renderWindow = window;
	clearColor = glm::vec4(0.0, 0.0, 0.0, 1.0);
}

void GLGI::Renderer::render(Scene * scene)
{
	GLenum error;
	scene->update();
	//manager->update();//TODO necessary?

	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//glDisable(GL_DEPTH_TEST);
	glm::vec4 black = glm::vec4(0.f, 0.f, 0.f, 1.f);
	glClearBufferfv(GL_COLOR, 0, &(black[0]));
	//glClearColor(clearColor[0], clearColor[1], clearColor[2], clearColor[3]);
	//float temp = clearColor[1];
	//clearColor[1] = clearColor[0];
	//clearColor[0] = temp;
	glClear(GL_DEPTH_BUFFER_BIT);

	// Activate simple shading program
	glUseProgram(programID);

	// Set up for a glDrawElements call
	//glBindVertexArray(manager->vaos);

	
	manager->enableBuffers();
	if ((error = glGetError()) != GL_NO_ERROR) {
		printf("OPENGL error: %d\n", error);
		error = 0;
	}
	
	int nl = manager->lights.size() < maxlights ? manager->lights.size() : maxlights;
	for (int i = 0; i < nl; i++) {
		Light * light = manager->lights[i];
		light->halfVector = glm::normalize(light->position + scene->currentCamera->getLookDirUnitVec());
		setLightUniform(i, *light);
		if ((error = glGetError()) != GL_NO_ERROR) {
			printf("OPENGL error: %d\n", error);
			error = 0;
		}
	}

	uint index = 0;
	Light l = Light();
	Light * light;

	if (manager->lights.size() > 0) {
		light = manager->lights[0];
	}
	else {
		light = &l;
	}

	light->halfVector = glm::normalize(light->position + scene->currentCamera->getLookDirUnitVec());
	light->calcPosition = glm::vec3(scene->currentCamera->getViewMatrix() * glm::vec4(light->position, 1.0));

	setLightUniform(index, *light);

	if (shadowProgramID != NULL){
		const glm::vec3 cubemapdirs[6] = { glm::vec3(0, -90, 0), glm::vec3(0, 90, 0), glm::vec3(90, 0, 0), glm::vec3(-90, 0, 0), glm::vec3(0, 180, 0), glm::vec3(0, 0, 0)  };
		for (int i = 0; i < nl; i++) {
			Light * light = manager->lights[i];
			Camera lightcam = Camera();

			lightcam.FOV = 90.f;
			lightcam.aspectRatio = 1.0f;
			lightcam.nearFace = 0.f;
			lightcam.farFace = 1000000000.f;


			for (int dirind = 0; dirind < 6; ++dirind) {
				lightcam.setPosition(light->position);
				lightcam.setRotation(cubemapdirs[dirind][0], cubemapdirs[dirind][1], cubemapdirs[dirind][2])
	;
				if (light->local) {
					lightcam.update();
				}
				glFramebufferTextureLayer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, shadowTexturesCubeMap, 0, i * 6 + dirind);
				//glFramebufferTexture3D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL, glcubemapdirs[dirind], manager->shadowTexturesCubeMap, 1, i);
				if ((error = glGetError()) != GL_NO_ERROR) {
					printf("OPENGL error: %d\n", error);
					error = GL_NO_ERROR;
				}

				for (unsigned int j = 0; j < scene->objects.size(); j++) {
					if (scene->objects[j]->isVisible()) {
						if (!light->local) {
							lightcam.setPosition(scene->objects[j]->getPosition() - glm::vec3(light->position[0] * 1000.f, light->position[1] * 1000.f, light->position[2] * 1000.f ));
							lightcam.update();
						}
						glm::mat4 mvp = lightcam.getPerspectiveMatrix() * lightcam.getViewMatrix() * scene->objects[j]->getModelMatrix();
						if ((error = glGetError()) != GL_NO_ERROR) {
							printf("OPENGL error: %d\n", error);
							error = GL_NO_ERROR;
						}
						glUniformMatrix4fv(mvpShadowUniform, 1, GL_FALSE, &(mvp[0][0]));
						if ((error = glGetError()) != GL_NO_ERROR) {
							printf("OPENGL error: %d\n", error);
							error = GL_NO_ERROR;
						}
						GLuint start = manager->getMeshStart(scene->objects[j]->getMesh());
						GLuint size = scene->objects[j]->getMesh()->size();

						unsigned short status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
						switch (status)
						{

						case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
							printf("incomplete attachment\n");
							break;

						case GL_FRAMEBUFFER_INCOMPLETE_DIMENSIONS_EXT:
							printf("incomplete dims\n");
							break;
						case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
							printf("incomplete missing attachment\n");
							break;
						case GL_FRAMEBUFFER_UNSUPPORTED:
							printf("unsupported\n");
							break;
						case GL_FRAMEBUFFER_COMPLETE:
							printf("complete\n");
							break;
						default:
							printf("unknown response\n");
							break;
						}
						printf("FrameBufferStatus= %x \n", &status);

						glDrawArrays(GL_TRIANGLES, start, size);
						if ((error = glGetError()) != GL_NO_ERROR) {
							printf("OPENGL error: %d\n", error);
							error = GL_NO_ERROR;
						}


					}
				}
			}
		}
	}


	if ((error = glGetError()) != GL_NO_ERROR) {
		printf("OPENGL error: %d\n", error);
		error = 0;
	}
	
	for (int i = 0; i < manager->materials.size(); ++i) {
		setMaterialUniform(index, *(manager->materials[i]));
	}

	if ((error = glGetError()) != GL_NO_ERROR) {
		printf("OPENGL error: %d\n", error);
		error = 0;
	}
	glm::vec3 eyedir = scene->currentCamera->getLookDirUnitVec();
	glUniform3f(eyeUniform, eyedir.x, eyedir.y, eyedir.z);
	
	if ((error = glGetError()) != GL_NO_ERROR) {
		printf("OPENGL error: %d\n", error);
		error = 0;
	}


	// Set up the model and projection matrix
	glm::mat4 perspective = scene->currentCamera->getPerspectiveMatrix();
	glm::mat4 view = scene->currentCamera->getViewMatrix();
	glm::mat4 vp = perspective * view;


	for (unsigned int i = 0; i < scene->objects.size(); i++) {
		if (scene->objects[i]->isVisible()) {
			glm::mat4 mvp = vp * scene->objects[i]->getModelMatrix();
			glm::mat4 mv = view * scene->objects[i]->getModelMatrix(); //view;// *scene->objects[i]->getModelMatrix();
			glm::mat4 m = scene->objects[i]->getModelMatrix();
			/*
			glm::mat4 mvp = vp * scene->objects[i]->getModelMatrix();
			glm::mat4 mv = scene->objects[i]->getModelMatrix(); //view;// *scene->objects[i]->getModelMatrix();
			glm::mat3 m = glm::mat3(scene->objects[i]->getModelMatrix());
			*/
			if ((error = glGetError()) != GL_NO_ERROR) {
				printf("OPENGL error: %d\n", error);
				error = 0;
			}
			glUniformMatrix4fv(mvpUniform, 1, GL_FALSE, &(mvp[0][0]));
			if ((error = glGetError()) != GL_NO_ERROR) {
				printf("OPENGL error: %d\n", error);
				error = 0;
			}
			glUniformMatrix4fv(mvUniform, 1, GL_FALSE, &(mv[0][0]));
			if ((error = glGetError()) != GL_NO_ERROR) {
				printf("OPENGL error: %d\n", error);
				error = 0;
			}
			glUniformMatrix4fv(mUniform, 1, GL_FALSE, &(m[0][0]));
			if ((error = glGetError()) != GL_NO_ERROR) {
				printf("OPENGL error: %d\n", error);
				error = 0;
			}
			GLuint start = manager->getMeshStart(scene->objects[i]->getMesh());
			GLuint size = scene->objects[i]->getMesh()->size();
			Texture * tex = scene->objects[i]->getTexture();
			GLint tid;
			if (tex == NULL) {
				tid = -1;
			}
			else {
				tid = manager->getTextureId(tex);
			}
			GLuint tuid = manager->getTextureUnitId(tex);
			//glUniform4f(ambientUniform, .7, 0.0, 0.7, 1.0);
			if ((error = glGetError()) != GL_NO_ERROR) {
				printf("OPENGL error: %d\n", error);
				error = 0;
			}
			glUniform1i(texUniform, tuid);
			if ((error = glGetError()) != GL_NO_ERROR) {
				printf("OPENGL error: %d\n", error);
				error = 0;
			}
			glUniform1i(texIDUniform, tid);
			if ((error = glGetError()) != GL_NO_ERROR) {
				printf("OPENGL error: %d\n", error);
				error = 0;
			}


			int mID;
			if (scene->objects[i]->getMaterial() == NULL) {
				mID = -1;
			}
			else {
				mID = manager->getMaterialId(scene->objects[i]->getMaterial());
			}
			
			glUniform1i(materialIndexUniform, 0);
			if ((error = glGetError()) != GL_NO_ERROR) {
				printf("OPENGL error: %d\n", error);
				error = 0;
			}

			int nlights;
			if (scene->objects[i]->isIgnoringLight()) {
				nlights = -1;
			}
			else {
				nlights = nl;
			}
			glUniform1i(numLightsUniform, nlights);
			if ((error = glGetError()) != GL_NO_ERROR) {
				printf("OPENGL error: %d\n", error);
				error = 0;
			}

			glDrawArrays(GL_TRIANGLES, start, size);
			
		}
	}
	glfwSwapBuffers(renderWindow->glfwwindow);
	manager->disableBuffers();

	glfwPollEvents();

}


void GLGI::Renderer::setLightUniform(uint index, GLGI::Light & light) {
	std::string prefix("Lights[");
	std::string suffix("].");
	std::string indstr = std::to_string(index);

	std::string member("enabled");
	std::string tmp = prefix + indstr + suffix + member;
	GLuint loc = glGetUniformLocation(programID, tmp.c_str());
	glUniform1i(loc, light.enabled);

	member = std::string("local");
	tmp = prefix + indstr + suffix + member;
	loc = glGetUniformLocation(programID, tmp.c_str());
	glUniform1i(loc, light.local);

	member = std::string("spot");
	tmp = prefix + indstr + suffix + member;
	loc = glGetUniformLocation(programID, tmp.c_str());
	glUniform1i(loc, light.spot);

	member = std::string("ambient");
	tmp = prefix + indstr + suffix + member;
	loc = glGetUniformLocation(programID, tmp.c_str());
	glUniform3f(loc, light.ambient[0], light.ambient[1], light.ambient[2]);

	member = std::string("color");
	tmp = prefix + indstr + suffix + member;
	loc = glGetUniformLocation(programID, tmp.c_str());
	glUniform3f(loc, light.color[0], light.color[1], light.color[2]);

	member = std::string("position");
	tmp = prefix + indstr + suffix + member;
	loc = glGetUniformLocation(programID, tmp.c_str());
	glUniform3f(loc, light.position[0], light.position[1], light.position[2]);

	member = std::string("halfVector");
	tmp = prefix + indstr + suffix + member;
	loc = glGetUniformLocation(programID, tmp.c_str());
	glUniform3f(loc, light.halfVector[0], light.halfVector[1], light.halfVector[2]);

	member = std::string("coneDirection");
	tmp = prefix + indstr + suffix + member;
	loc = glGetUniformLocation(programID, tmp.c_str());
	glUniform3f(loc, light.coneDirection[0], light.coneDirection[1], light.coneDirection[2]);

	member = std::string("spotCosCutoff");
	tmp = prefix + indstr + suffix + member;
	loc = glGetUniformLocation(programID, tmp.c_str());
	glUniform1f(loc, light.spotCosCutoff);

	member = std::string("spotExponent");
	tmp = prefix + indstr + suffix + member;
	loc = glGetUniformLocation(programID, tmp.c_str());
	glUniform1f(loc, light.spotExponent);

	member = std::string("constantAttenuation");
	tmp = prefix + indstr + suffix + member;
	loc = glGetUniformLocation(programID, tmp.c_str());
	glUniform1f(loc, light.constantAttenuation);

	member = std::string("linearAttenuation");
	tmp = prefix + indstr + suffix + member;
	loc = glGetUniformLocation(programID, tmp.c_str());
	glUniform1f(loc, light.linearAttenuation);

	member = std::string("quadraticAttenuation");
	tmp = prefix + indstr + suffix + member;
	loc = glGetUniformLocation(programID, tmp.c_str());
	glUniform1f(loc, light.quadraticAttenuation);
}

void GLGI::Renderer::setMaterialUniform(uint index, GLGI::Material & material) {
	std::string prefix("materials[");//lowercase "M" you idiot!
	std::string suffix("].");
	std::string indstr = std::to_string(index);


	std::string member = std::string("emission");
	std::string tmp = prefix + indstr + suffix + member;
	GLuint loc = glGetUniformLocation(programID, tmp.c_str());
	glUniform3f(loc, material.emission[0], material.emission[1], material.emission[2]);

	member = std::string("ambient");
	tmp = prefix + indstr + suffix + member;
	loc = glGetUniformLocation(programID, tmp.c_str());
	glUniform3f(loc, material.ambient[0], material.ambient[1], material.ambient[2]);

	member = std::string("diffuse");
	tmp = prefix + indstr + suffix + member;
	loc = glGetUniformLocation(programID, tmp.c_str());
	glUniform3f(loc, material.diffuse[0], material.diffuse[1], material.diffuse[2]);

	member = std::string("specular");
	tmp = prefix + indstr + suffix + member;
	loc = glGetUniformLocation(programID, tmp.c_str());
	glUniform3f(loc, material.specular[0], material.specular[1], material.specular[2]);

	member = std::string("shininess");
	tmp = prefix + indstr + suffix + member;
	loc = glGetUniformLocation(programID, tmp.c_str());
	glUniform1f(loc, material.shininess);
}
