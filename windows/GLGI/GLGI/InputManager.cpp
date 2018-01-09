#include "stdafx.h"
#include "GLGI.h"

GLGI::InputManager::InputManager(Window * window) {
	//glfwSetKeyCallback(window->glfwwindow, (GLFWkeyfun) &this->keyCallBack);
	attach(window);
}

GLGI::InputManager::InputManager()
{

}

GLGI::Window * GLGI::InputManager::detach()
{
	Window * temp = attachedWindow;
	attachedWindow = nullptr;
	if (temp != nullptr && temp->getInputManager() != nullptr) {
		temp->detachInputManager();
	}
	return temp;
}

void * GLGI::InputManager::attach(Window * window)
{
	
	glfwSetKeyCallback(window->glfwwindow, [](GLFWwindow * w, int i, int j, int k, int l) {
		static_cast<GLGI::Window *>(glfwGetWindowUserPointer(w))->input->keyCallBack(w, i, j, k, l);
	});
	glfwSetKeyCallback(window->glfwwindow, [](GLFWwindow * w, int i, int j, int k, int l) {
		static_cast<GLGI::Window *>(glfwGetWindowUserPointer(w))->input->keyCallBack(w, i, j, k, l);
	});
	glfwSetKeyCallback(window->glfwwindow, [](GLFWwindow * w, int i, int j, int k, int l) {
		static_cast<GLGI::Window *>(glfwGetWindowUserPointer(w))->input->keyCallBack(w, i, j, k, l);
	});
}

void GLGI::InputManager::keyCallBack(GLFWwindow * window, int button, int scancode, int action, int mods)
{
	for (int i = 0; i < keyFunctions.size(); i++) {
		if (keys[i] == button) {
			keyFunctions[i](button, action, mods);
		}
	}
}

void GLGI::InputManager::mousePosCallBack(GLFWwindow *, double x, double y)
{

	for (int i = 0; i < mousePosFunctions.size(); i++) {
		mousePosFunctions[i](x,y);
	}

}

void GLGI::InputManager::addKeyFunction(int key, KeyFuncType keyfunc)
{

	keys.push_back(key);
	keyFunctions.push_back(keyfunc);

}

void GLGI::InputManager::removeAllKeyFunctions(int key) {
	for (int i = 0; i < keys.size(); i++) {
		if (keys[i] == key) {
			keys.erase(keys.begin() + i);
			keyFunctions.erase(keyFunctions.begin() + i);
		}
	}
}

void GLGI::InputManager::removeKeyFunction(KeyType key, KeyFuncType keyFunc)
{
	for (int i = 0; i < keys.size(); i++) {
		if (keys[i] == key && keyFunc == keyFunctions[i]) {
			keys.erase(keys.begin() + i);
			keyFunctions.erase(keyFunctions.begin() + i);
		}
	}
}



