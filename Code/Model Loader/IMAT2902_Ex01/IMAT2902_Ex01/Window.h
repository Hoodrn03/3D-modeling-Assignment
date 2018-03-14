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

#include "Win32OpenGL.h"
#include "resource.h"

#include "LoadObject.h"



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

	// Camera Possition Coordinates.
	float m_cameraX{ 0 };
	float m_cameraY{ 0 };
	float m_cameraZ{ 0.0f };

	glm::mat4 m_viewMatrix;
	glm::mat4 m_projectionMatrix;
	glm::mat4 m_modelMatrix;

	vector<float> m_vertices;			// We can't initialise at compile time

	GLuint m_vao;
	GLuint m_vboVertices;


	float m_xAngle{ 0.0f };
	float m_zAngle{ 0.0f };

	float m_aspectRatio;

	LoadObject loadObject; 

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
	
	void ComputeViewMatrix();
	
	
};

