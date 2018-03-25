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
										
	// MessageBoxA(0, (char*)glGetString(GL_VERSION), "OPENGL VERSION", 0);
	m_aspectRatio = static_cast<float>(rect.right / rect.bottom);


	// TODO try these shaders later
	
	// m_win32OpenGL.CreateShadersAndProgram("flat");
	// m_win32OpenGL.CreateShadersAndProgram("flatVerticesAsColours");
	m_win32OpenGL.CreateShadersAndProgram("flatFixedColour");


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
	loadObject.m_loadobj("Models/Test_Objects/simpleCube.obj");

	ComputeProjectionMatrix();
	
	camera.ComputeDirectionVector();
	camera.ComputeViewMatrixUsingLookAt();

	// send the matrices to the shader
	
	program = m_win32OpenGL.GetShaderProgram();
	
	camera.SetViewMatrix(program);

	Win32OpenGL::SendUniformMatrixToShader(program, m_projectionMatrix, "projection_matrix");

	

	testItems.m_CreateCube();

	int numberOfElements = testItems.m_GetVertices().size();

	for (int i = 0; i < numberOfElements; i++)
	{
		m_vertices.push_back(testItems.m_GetVertices().at(i));
	} 




	// later we can use Win32OpenGL::CreateVAO(m_vao, m_vboVertices, vertices);
	
	// create the vertex buffer object - the vbo

	glGenBuffers(1, &m_vboVertices);
	glBindBuffer(GL_ARRAY_BUFFER, m_vboVertices);
	glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(GLfloat), &m_vertices[0], GL_STATIC_DRAW);

	// create the vertex array object - the vao

	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);
	glBindBuffer(GL_ARRAY_BUFFER, m_vboVertices);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	
	// vertices are element 0 in VAO (the only element currently)
	
	glEnableVertexAttribArray(0);


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
	
	// set up the model matrix - we could do this in the update!!!!
	m_modelMatrix = glm::mat4(1.0f);	// identity matrix;
	
	m_modelMatrix = glm::rotate(m_modelMatrix, (float)glm::radians(m_xAngle), glm::vec3(1.0f, 0.0f, 0.0f));
	m_modelMatrix = glm::rotate(m_modelMatrix, (float)glm::radians(m_zAngle), glm::vec3(0.0f, 0.0f, 1.0f));

	// m_modelMatrix = glm::scale(m_modelMatrix, glm::vec3(30, 30, 30)); 

	Win32OpenGL::SendUniformMatrixToShader(program, m_modelMatrix, "model_matrix");


	glBindVertexArray(m_vao); // select first VAO
	
	GLuint numberOfElements = m_vertices.size() / 3;
	
	glDrawArrays(GL_TRIANGLES, 0, numberOfElements); // draw first object
	
	glBindVertexArray(0);


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

