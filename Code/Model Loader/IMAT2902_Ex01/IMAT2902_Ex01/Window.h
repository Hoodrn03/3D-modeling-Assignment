/*!\file Window.h
*
* This class will be used to create and handle the openGL window, 
* it will control all of the functions regarding the window; including 
* drawing and updating. 
*
*/


#pragma once

//  for M_PI constant
#define _USE_MATH_DEFINES

#include "defs.h"

#include "Camera.h"
#include "TestItems.h"
#include "Model.h"

class Window
{
	// Constructor 

public:

	Window();

	// Deconstructor 

public:

	~Window();

	// Data Members 

private:

	// open gl helper class.
	Win32OpenGL m_win32OpenGL;

	glm::mat4 m_projectionMatrix;
	glm::mat4 m_modelMatrix;

	vector<float> m_vertices;			// We can't initialise at compile time

	// new for lighting
	vector<float> m_normals;

	GLuint m_vao;
	GLuint m_vboVertices;

	// new for lighting
	GLuint m_vboNormals;

	float m_xAngle{ 0.0f };
	float m_zAngle{ 0.0f };
	float m_yAngle{ 0.0f };

	float m_aspectRatio;

	// new for lighting

	glm::vec3 m_lightColourSpecular{ 1.0f,1.0f,1.0f };
	glm::vec3 m_lightColourDiffuse{ 0.8f, 0.8f, 0.8f };
	glm::vec3 m_lightColourAmbient{ 0.3f, 0.3f, 0.3f };
	glm::vec3 m_lightPosition{ 0.0f, 5.0f, 5.0f };



	GLuint VAO;

	GLuint program;

	// Classes : 
	
	Camera camera;

	TestItems testItems; 

	Model m_model;

	std::vector<Model> v_Scene; 

	// Memebr Functions 

public: 

	void CreateGLWindow(HWND hWnd, RECT rect);

	void DestroyGLWindow();

	void PrepareToDraw();

	void Draw();

	void Update();

	void HandleInput(unsigned char virtualKeyCode);

	void Resize(HDC hdc, RECT rect);

	void ComputeProjectionMatrix();
	
	
	
};

