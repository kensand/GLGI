// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the GLGI_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// GLGI_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef GLGI_EXPORTS
#define GLGI_API __declspec(dllexport)
#else
#define GLGI_API __declspec(dllimport)
#endif



#include <map>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <common/texture.hpp>
#include <common/objloader.hpp>
#include <common/shader.hpp>

#include <tinyobjloader/tiny_obj_loader.h>

#define GLM_ENABLE_EXPERIMENTAL 1
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>
#include <vector>
#include <sstream>


#include "Defines.h"
//#include "Util.h"

/*template <class T>
void DBOUT( T s )            \
{                             \
   std::wostringstream os_;    \
   os_ << s;                   \
   OutputDebugStringW( os_.str().c_str() );  \
}*/


namespace GLGI {
	

	


	

	const glm::vec3 xAxis = glm::vec3(1, 0, 0);
	const glm::vec3 yAxis = glm::vec3(0, 1, 0);
	const glm::vec3 zAxis = glm::vec3(0, 0, -1);

	struct GLGI_API PackedVertex {
		glm::vec3 position;
		glm::vec3 normal;
		glm::vec4 color;
		glm::vec2 uv;
		PackedVertex(glm::vec3 Position, glm::vec2 UV, glm::vec3 Normal, glm::vec4 Color = glm::vec4(0.f, 0.f, 0.f, 1.f));
		PackedVertex(const PackedVertex & copy);
		bool operator<(const PackedVertex that) const;
	};

	struct GLGI_API Mesh {
		std::vector<PackedVertex> vertices;
		Mesh(const char * path, glm::vec4 color=glm::vec4(0.f, 0.f, 0.f, 0.f));
		
		PackedVertex operator[](unsigned int i) { return vertices[i]; };
		size_t size() { return vertices.size(); };
	};


	class GLGI_API Texture {
	public:
		Texture(const char * path);
		~Texture();
		//std::vector <unsigned char> data;
		
		unsigned int imageSize;
		unsigned int width, height, channels;
		const unsigned char * getDataLoc() { return (const unsigned char *) data; }
	private:
		unsigned char * data;
		const char * imagepath;
	};

	
	

	class GLGI_API Camera {
		friend class Scene;
	public:
		Camera();
		void update();
		void setPosition(GLfloat x, GLfloat y, GLfloat z);


		void setPosition(glm::vec3 coords);


		void setRotation(GLfloat x, GLfloat y, GLfloat z);


		void setRotation(glm::vec3 axisRot);
		void setScale(glm::vec3 scale);

		glm::vec3 getLookDirUnitVec();
		glm::vec3 getRotation();
		glm::vec3 getPosition();
		glm::mat4 getViewMatrix();
		glm::mat4 getPerspectiveMatrix();
		glm::vec3 getScale();
		glm::mat4 getRotationMatrix();
		


	private:
		
		glm::mat4 PerspectiveMatrix;
		glm::mat4 ViewMatrix;
		glm::vec3 CameraLocation;
		glm::vec3 CameraRotation;
		glm::vec3 CameraScale;
		glm::vec3 LookDirUnitVec;
		
	};

	class GLGI_API Light {
	public:
		Light();

		bool enabled;
		bool local;

		bool spot;
		glm::vec3 ambient;
		glm::vec3 color;
		glm::vec3 position;

		glm::vec3 halfVector;
		glm::vec3 coneDirection;

		float spotCosCutoff;
		float spotExponent;
		float constantAttenuation;
		float linearAttenuation;
		float quadraticAttenuation;
		glm::vec3 calcPosition;

	};

	class GLGI_API Material {
	public:
		Material();
		glm::vec3 emission;
		glm::vec3 ambient;
		glm::vec3 diffuse;
		glm::vec3 specular;
		float shininess;
	};

	class GLGI_API Object {
		friend class Scene;
	public:
		Object();
		template <typename T>
		void setPosition(T x, T y, T z) {
			this->ModelLocation[0] = (GLfloat)x;
			this->ModelLocation[1] = (GLfloat)y;
			this->ModelLocation[2] = (GLfloat)z;
			this->update();
		}

		template <typename T>
		void setPosition(T coords) {
			this->ModelLocation[0] = (GLfloat)coords[0];
			this->ModelLocation[1] = (GLfloat)coords[1];
			this->ModelLocation[2] = (GLfloat)coords[2];
			this->update();
		}

		template <typename T>
		void setRotation(T x, T y, T z) {
			this->ModelRotation[0] = (GLfloat)x;
			this->ModelRotation[1] = (GLfloat)y;
			this->ModelRotation[2] = (GLfloat)z;
			this->update();
		}

		template <typename T>
		void setRotation(T axisRot) {
			this->ModelRotation[0] = (GLfloat)axisRot[0];
			this->ModelRotation[1] = (GLfloat)axisRot[1];
			this->ModelRotation[2] = (GLfloat)axisRot[2];
			this->update();
		}

		void setScale(glm::vec3 scale);

		glm::vec3 getRotation();
		glm::vec3 getPosition();
		glm::mat4 getModelMatrix();
		glm::vec3 getScale();
		bool isIgnoringLight() { return ignoreLights; };
		bool isVisible() { return visible; };
		void setIgnoreLight(bool ignore) { ignoreLights = ignore; };
		void setVisible(bool Visible) { visible = Visible; };
		void update();

		Mesh * getMesh() { return mesh; };
		void setMesh(Mesh * m) { mesh = m; };

		Texture * getTexture() { return texture; };
		void setTexture(Texture * t) { texture = t; };

		Material * getMaterial() { return material; };
		void setMaterial(Material * m) { material = m; };


	private:
		Texture * texture;
		Mesh * mesh;
		Material * material;
		bool visible;
		bool ignoreLights;
		glm::mat4 ModelMatrix;
		glm::vec3 ModelLocation;
		glm::vec3 ModelRotation;
		glm::vec3 ModelScale;
	};


	/*Scene - an object to represent the scene as a whole.
	*/
	class GLGI_API Scene {
		friend class Renderer;
	public:
		Scene();
		Object * createObject(const char * wavefront_obj);
		void destroyObject(Object*);
		void addObject(Object * o);
		void addCamera(Camera * c);
		Camera * createCamera();
		void update();
		Camera * currentCamera;
		std::vector<Object *> objects;
		std::vector<Camera *> cameras;
	private:
		
	};

	
	typedef GLGI_API long ResourceId;



	class GLGI_API ResourceManager {
		friend class Renderer;
	private:
		std::vector <Mesh *> meshes;
		std::vector <size_t> meshStarts;
		std::vector <PackedVertex> vertices;
		std::vector <Texture *> textures;
		std::vector <GLint> textureUnitIds;
		std::vector <Light *> lights;
		std::vector <Material *> materials;
		static const int numResourceTypes = 2;
		int numTextures;
		GLuint vaos;
		GLuint vbos[numResourceTypes];
		GLuint ebos[numResourceTypes];
		GLuint * textureIdArr;

		GLuint textures2D;
		GLuint texdims2D[2];

		
	public:
		enum vertexAttributes {positions = 0, normals, colors, uvs};
		ResourceManager();
		~ResourceManager();
		ResourceId addResource(Mesh * mesh);
		ResourceId addResource(Texture * texture);
		ResourceId addResource(Light * light);
		ResourceId addResource(Material * material);
		void update();
		void enableBuffers();
		void disableBuffers();
		GLuint getMeshStart(Mesh * mesh);
		GLuint getTextureUnitId(Texture * texture);
		GLuint getTextureId(Texture * texture);
		GLuint getMaterialId(Material * material);


		
	private:
	};

	class GLGI_API Window;

	

	class GLGI_API InputManager {
	public:

		virtual class GLGI_API BaseKeyInputClass {
		public:
			virtual void operator()(int key, int state, int mods) {};
			virtual void update() {};
		};

		virtual class GLGI_API BaseMousePosClass {
		public:
			virtual void operator()(double x, double y) = 0;
			virtual void update() = 0;
		};

		typedef int KeyType;
		typedef int StateType;
		typedef int MouseButtonType;
		typedef int ModType;

		typedef BaseKeyInputClass * KeyFuncType; //void(*KeyFuncType) (KeyType key, StateType state, ModType mods);
		typedef BaseMousePosClass * MousePosFuncType;//void(*MousePosFuncType) (double xpos, double ypos);
		typedef void(*MouseButtonFuncType) (MouseButtonType mouseButton, StateType mouseButtonState, ModType mods);

		InputManager(Window * window);
		InputManager();

		Window * detach();
		Window * getCurrentWindow();
		void attach(Window * window);



		void keyCallBack(GLFWwindow *, int, int, int, int);
		void mousePosCallBack(GLFWwindow *, double, double);
		void addKeyFunction(int key, KeyFuncType keyfunc);
		void removeAllKeyFunctions(int key);
		void addMousePosFunction(MousePosFuncType fun);
		void removeKeyFunction(KeyType, KeyFuncType);
		bool hasMousePosFun(MousePosFuncType fun);
		void removeMousePosFunction(MousePosFuncType fun);

		

	private:
		Window * attachedWindow;
		std::vector<KeyType> keys;
		std::vector<KeyFuncType> keyFunctions;

		std::vector<MousePosFuncType> mousePosFunctions;

		std::vector<MouseButtonType> mouseButtons;
		std::vector<MouseButtonFuncType> mouseButtonFunctions;


	};

	

	


	class GLGI_API Window {
		friend class Renderer;
		friend class InputManager;
	private:
		
		GLFWwindow* glfwwindow;
		InputManager * input;
		double mouseX, mouseY;
		int mouseState;

	public:
		double getMouseX() {
			return mouseX;
		}
		double getMouseY() {
			return mouseY;
		}
		double getKey(int key) {
			return glfwGetKey(this->glfwwindow, key);
		}

		static void GLGI::Window::cursorPosCallBack(GLFWwindow* window, double xpos, double ypos);
		static Window * currentWindow;
		Window();
		~Window();
		double getTime() { return glfwGetTime(); }
		void makeCurrentWindow() {
			currentWindow = this;
		}
		bool isCurrentWindow() {
			return currentWindow == this;
		}
		void makeCurrentContext();
		bool shouldClose();
		void close();
		void draw();

		/*Creates a new InputManager for this window and makes it the currently used Input manager.
		If no other Input manager is present, Null * is Returned, 
		other wise the newly detatched Input Manager is returned*/
		InputManager * createInputManager();
		InputManager * swapInputManager(InputManager * newInputManager);
		InputManager * getInputManager() { return input; }		// TODO: add your methods here.
		InputManager * detachInputManager();
		InputManager * attachInputManager(InputManager * newInputManager);
		
		int getMouseState() { return mouseState; }
		void setMouseState(int state);

	};

	class GLGI_API Renderer {
	public:
		Renderer(ResourceManager * resourceManager, Window * window, const char * vertexshaderpath, const char * fragmentshaderpath);
		void render(Scene * scene);
		const int maxlights = 10;
		

	private:
		GLuint programID;
		Window * renderWindow;
		ResourceManager * manager;
		GLint mvpUniform;
		GLint mvUniform;
		GLint mUniform;
		GLint texUniform;
		GLint texIDUniform;
		GLint ambientUniform;
		GLint eyeUniform;
		GLint materialIndexUniform;
		GLint numLightsUniform;
		glm::vec4 clearColor;
		void setLightUniform(uint index, Light & light);
		void setMaterialUniform(uint index, Material & material);
	};	


	/*example Input Manager Classes*/
	class CamMove : public GLGI::InputManager::BaseKeyInputClass {
	private:
		double speed;
		GLGI::Camera * cam;
		bool pressed;
		glm::vec3 dir;
		GLGI::InputManager::KeyType k;
	public:
		void update() {
			if (pressed) {
				glm::vec3 pos = cam->getPosition();
				glm::vec3 add = glm::vec3(glm::vec4(dir, 0) * cam->getRotationMatrix());
				cam->setPosition(pos + add);
			}
		}
		void operator()(int key, int state, int mods)  {
			if (key == k && state == GLGI_PRESS) {
				pressed = true;
			}
			else if (key == k && state == GLGI_RELEASE) {
				pressed = false;
			}
		};
		CamMove(GLGI::InputManager::KeyType triggerKey, GLGI::Camera * camera, double moveSpeed, glm::vec3 direction) {
			cam = camera;
			dir = direction;
			speed = moveSpeed;
			pressed = false;
			k = triggerKey;
		}
	};

	class MouseToggle : public GLGI::InputManager::BaseKeyInputClass {
	private:
		GLGI::InputManager::KeyType k;
		GLGI::Window * win;
		GLGI::InputManager * im;
		GLGI::InputManager::BaseMousePosClass * f;
		int on, off;
		
	public:
		void update() {
			
		}
		void operator()(int key, int state, int mods) {
			if (key == k && state == GLGI_PRESS) {
				
			}
			else if (key == k && state == GLGI_RELEASE) {
				if (im->hasMousePosFun(f)) {
					im->removeMousePosFunction(f);
					if (win->getMouseState() != off) {
						win->setMouseState(off);
					}
				}
				else {
					im->addMousePosFunction(f);
					if (win->getMouseState() != on) {
						win->setMouseState(on);
					}
				}

			}
		};
		MouseToggle(GLGI::Window * w, GLGI::InputManager::KeyType triggerKey, GLGI::InputManager * inputManager, GLGI::InputManager::BaseMousePosClass * mousePos, int onState, int offState) {
			im = inputManager;
			on = onState;
			off = offState;
			f = mousePos;
			win = w;
			k = triggerKey;
		}
	};

	class CamRotate : public GLGI::InputManager::BaseMousePosClass {
	private:
		double speed;
		GLGI::Camera * cam;
		GLGI::Window * win;
		glm::vec3 dir;
		double lastx, lasty;
	public:
		void update() {

		}
		void operator()(double xpos, double ypos) {
			win->setMouseState(GLGI_CURSOR_DISABLED);

			glm::vec3 newRot = cam->getRotation() + glm::vec3((ypos - lasty) * speed, (xpos - lastx) * speed, 0.);
			newRot[0] = fmod(newRot[0] + 90.f, 180) - 90.f;
			cam->setRotation(newRot);
			
			lasty = ypos;
			lastx = xpos;
		};

		CamRotate(GLGI::Window * window, GLGI::Camera * camera, double rotSpeed) {
			cam = camera;
			lastx = lasty = 0.;
			speed = rotSpeed;
			win = window;

		}
	};

	// This class is exported from the GLGI.dll
	
}

extern GLGI_API int nGLGI;

GLGI_API int fnGLGI(void);
