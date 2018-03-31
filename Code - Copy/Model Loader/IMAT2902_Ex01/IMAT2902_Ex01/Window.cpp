/*!\file Window.cpp
*
* This will hold all of the function definitions for the class Window.
*
*/

#include "stdafx.h"
#include "Window.h"


//! This is the constructor for the Window class. 
/*!
/
*/
Window::Window()
{
	// we don't use RAII currently so no action in constructor

	// Model model;

	// model.m_LoadModel("Models/Structures/Grass.obj");

	// v_Scene.push_back(model); 

	Model model_Two;

	model_Two.m_LoadModel("Models/Test_Objects/simpleCubeWithMaterials.obj");

	v_Scene.push_back(model_Two);

}

//-------------------------------------------------------------------------------------------------

//! This is the deconstructor for the Window class 
/*!
/
*/
Window::~Window()
{

}

//-------------------------------------------------------------------------------------------------

//! This is used to create the display window. 
/*!
/
*/
void Window::CreateGLWindow(HWND hWnd, RECT rect)
{
	/*
		this code is called from a WM_CREATE message in winproc
	*/


	m_win32OpenGL.CreateGLContext(hWnd);	// may throw an exception!!!
										
	m_aspectRatio = static_cast<float>(rect.right / rect.bottom);


	// TODO try these shaders later
	
	m_win32OpenGL.CreateShadersAndProgram("phong");


	m_win32OpenGL.SetupDisplay();

	m_win32OpenGL.GetError();			// check all ok


}

//-------------------------------------------------------------------------------------------------

//! This is used to destroy the display window. 
/*!
/
*/
void Window::DestroyGLWindow()
{
	/*
		called from a WM_DESTROY message
	*/
	m_win32OpenGL.TearDownGLContext();
}


//-------------------------------------------------------------------------------------------------

//! This is used to setup for drawing. 
/*!
/
*/
void Window::PrepareToDraw()
{

	ComputeProjectionMatrix();
	

	// Compute View Matrix 
	camera.ComputeDirectionVector();
	camera.ComputeViewMatrixUsingLookAt();

	// send the matrices to the shader
	
	program = m_win32OpenGL.GetShaderProgram();
	
	camera.SetViewMatrix(program);

	Win32OpenGL::SendUniformMatrixToShader(program, m_projectionMatrix, "projection_matrix");

	// Lighting 

	Win32OpenGL::SendUniformVector3ToShader(program, m_lightPosition, "light_position_world");
	Win32OpenGL::SendUniformVector3ToShader(program, m_lightColourSpecular, "light_colour_specular");
	Win32OpenGL::SendUniformVector3ToShader(program, m_lightColourDiffuse, "light_colour_diffuse");
	Win32OpenGL::SendUniformVector3ToShader(program, m_lightColourAmbient, "light_colour_ambient");

	// m_model.m_PrepareModel();

	for (unsigned int i = 0; i < v_Scene.size(); i++)
	{
		v_Scene.at(i).m_PrepareModel();
	}


	m_win32OpenGL.GetError();			// check all ok
}


//-------------------------------------------------------------------------------------------------

//! This is used to draw objects into the game world. 
/*!
/
*/
void Window::Draw()
{
	m_win32OpenGL.ClearGLDisplay();

	GLuint program = m_win32OpenGL.GetShaderProgram();

	// TODO - Add drawing Code Here

	// m_model.m_DrawModels();

	for (unsigned int i = 0; i < v_Scene.size(); i++)
	{
		v_Scene.at(i).m_DrawModels();
	}

	// First Cube. 

	// send a colour to the shader - used if we run the flat shader
	glm::vec3 colour{ 1.0f, 0.0f, 0.0f };
	Win32OpenGL::SendUniformVector3ToShader(program, colour, "surface_colour");

	m_modelMatrix = glm::mat4(1.0f);
	
	Win32OpenGL::SendUniformMatrixToShader(program, m_modelMatrix, "model_matrix");


	Win32OpenGL::FinishedDrawing();
	Win32OpenGL::GetError();			// check all ok
}

//-------------------------------------------------------------------------------------------------

//! This is used to update everything, (It can be used for animation). 
/*!
/
*/
void Window::Update()
{
	// Add any animation here 

}

//-------------------------------------------------------------------------------------------------

//! This is used to handle any input from the user. 
/*!
/
*/
void Window::HandleInput(unsigned char virtualKeyCode)
{

	camera.HandleInput(virtualKeyCode); 

	program = m_win32OpenGL.GetShaderProgram();

	camera.SetViewMatrix(program);

}

//-------------------------------------------------------------------------------------------------

//! This is used to resize the display window. 
/*!
/
*/
void Window::Resize(HDC hdc, RECT rect)
{
	// if the display is resized then OpenGL needs to know about the apect ratio
	// to compute the correct projection matrix
	m_win32OpenGL.Reshape(hdc, rect.right, rect.bottom);

	m_aspectRatio = (float)rect.right / rect.bottom;
	
	ComputeProjectionMatrix();
	
	GLuint program = m_win32OpenGL.GetShaderProgram();
	
	Win32OpenGL::SendUniformMatrixToShader(program, m_projectionMatrix, "projection_matrix");
	
	m_win32OpenGL.GetError();			// check all ok
}

//-------------------------------------------------------------------------------------------------

//!
/*!
/
*/
void Window::ComputeProjectionMatrix()
{
	// we will look at this later in the course
	
	// in Modern OpenGL we must supply a projection matrix
	
	const float oneDegreeInRadians = static_cast<float>((2.0 * M_PI) / 360.0);
	
	//ONE_DEG_IN_RAD (2.0 * M_PI) / 360.0 // 0.017444444

	// input variables
	float zNear = 0.1f;		// clipping plane
	float zFar = 100.0f;	// clipping plane
	
	float fov = static_cast<float>(67.0f * oneDegreeInRadians); // convert 67 degrees to radians

	float range = tan(fov * 0.5f) * zNear;
	
	float Sx = (2.0f * zNear) / (range * m_aspectRatio + range * m_aspectRatio);
	float Sy = zNear / range;
	float Sz = -(zFar + zNear) / (zFar - zNear);
	float Pz = -(2.0f * zFar * zNear) / (zFar - zNear);
	
	GLfloat proj_mat[] = {
		Sx, 0.0f, 0.0f, 0.0f,
		0.0f, Sy, 0.0f, 0.0f,
		0.0f, 0.0f, Sz, -1.0f,
		0.0f, 0.0f, Pz, 0.0f
	};
	
	m_projectionMatrix = glm::make_mat4(proj_mat);
}

//-------------------------------------------------------------------------------------------------

