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
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>
#include <common\texture.hpp>
#include <common\objloader.hpp>
#include <common\shader.hpp>


#define GLM_ENABLE_EXPERIMENTAL 1
#include <glm\gtx\transform.hpp>
#include <string>
#include <vector>

#include <sstream>
template <class T>
void DBOUT( T s )            \
{                             \
   std::wostringstream os_;    \
   os_ << s;                   \
   OutputDebugStringW( os_.str().c_str() );  \
}


namespace GLGI {




	

	const glm::vec3 xAxis = glm::vec3(1, 0, 0);
	const glm::vec3 yAxis = glm::vec3(0, 1, 0);
	const glm::vec3 zAxis = glm::vec3(0, 0, -1);

	struct GLGI_API PackedVertex {
		PackedVertex(glm::vec3 Position, glm::vec2 UV, glm::vec3 Normal);
		PackedVertex(const PackedVertex & copy);

		glm::vec3 position;
		glm::vec2 uv;
		glm::vec3 normal;
		bool operator<(const PackedVertex that) const;
	};

	struct GLGI_API Mesh {
		std::vector<PackedVertex> vertices;
		Mesh(const char * path);
		
		PackedVertex operator[](unsigned int i) { return vertices[i]; };
		size_t size() { return vertices.size(); };
	};


	class GLGI_API Texture {
	public:
		Texture();
	private:

	};
	

	class GLGI_API Camera {
	public:
		Camera();
		template <typename T>
		void setPosition(T x, T y, T z);

		template <typename T>
		void setPosition(T coords);

		template <typename T>
		void setRotation(T x, T y, T z);

		template <typename T>
		void setRotation(T axisRot);

		void setScale(glm::vec3 scale);

		glm::vec3 getRotation();
		glm::vec3 getPosition();
		glm::mat4 getViewMatrix();
		glm::mat4 getPerspectiveMatrix();
		glm::vec3 getScale();
		void update();


	private:
		glm::mat4 PerspectiveMatrix;
		glm::mat4 ViewMatrix;
		glm::vec3 CameraLocation;
		glm::vec3 CameraRotation;
		glm::vec3 CameraScale;

	};



	class GLGI_API Object {
	public:
		Object();
		template <typename T>
		void setPosition(T x, T y, T z);

		template <typename T>
		void setPosition(T coords);

		template <typename T>
		void setRotation(T x, T y, T z);

		template <typename T>
		void setRotation(T axisRot);

		void setScale(glm::vec3 scale);

		glm::vec3 getRotation();
		glm::vec3 getPosition();
		glm::mat4 getModelMatrix();
		glm::vec3 getScale();
		
		bool isVisible() { return visible; };
		void update();

		Mesh * getMesh() { return mesh; };
		void setMesh(Mesh * m) { mesh = m; };


	private:
		Texture * texture;
		Mesh * mesh;
		bool visible;
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
		void addObject(Object * o);
		void addCamera(Camera * c);
		void update();
	private:
		Camera * currentCamera;
		std::vector<Object *> objects;
		std::vector<Camera *> cameras;
	};

	
	typedef GLGI_API long ResourceId;
	class GLGI_API ResourceManager {
		friend class Renderer;
	private:
		std::vector <Mesh *> meshes;
		std::vector <size_t> meshStarts;
		std::vector <PackedVertex> vertices;
		static const int numResourceTypes = 2;
		GLuint vaos;
		GLuint vbos[numResourceTypes];
		GLuint ebos[numResourceTypes];


		
	public:
		enum vertexAttributes {positions = 0, uvs, normals};
		ResourceManager();
		~ResourceManager();
		ResourceId addResource(Mesh * mesh);
		ResourceId addResource(Texture * texture);
		void update();
		GLuint getMeshStart(Mesh * mesh);


		
	private:
	};


	class GLGI_API Window {
		friend class Renderer;
	private:
		GLFWwindow* glfwwindow;



	public:
		Window(void);
		double getTime() { return glfwGetTime(); }
		void makeCurrentContext();
		bool shouldClose();
		void close();
		void draw();
		// TODO: add your methods here.
	};

	class GLGI_API Renderer {
	public:
		Renderer(ResourceManager * resourceManager, Window * window);
		void render(Scene * scene);
		

	private:
		GLuint programID;
		Window * renderWindow;
		ResourceManager * manager;
		GLuint mvpUniform;
		

	};

	

	
	

	// This class is exported from the GLGI.dll
	
}

extern GLGI_API int nGLGI;

GLGI_API int fnGLGI(void);
