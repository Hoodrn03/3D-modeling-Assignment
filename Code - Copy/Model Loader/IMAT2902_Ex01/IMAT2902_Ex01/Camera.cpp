/*!\file Camera.cpp
*
* This will hold all of the function definitions for the class Camera.
*
*/

#include "stdafx.h"
#include "Camera.h"


//! This is the constructor for the Camera class. 
/*!
/
*/
Camera::Camera()
{

}

//-------------------------------------------------------------------------------------------------

//! This is the deconstructor for the Camera class. 
/*!
/
*/
Camera::~Camera()
{

}


//-------------------------------------------------------------------------------------------------

/*! 
This will be used to prepare the view matrix when it is called, is important to have this ready before trying to
display the window. 
*/
/*!
/
*/
void Camera::ComputeViewMatrixUsingLookAt()
{
	// float eyeX = m_x;
	// float eyeY = m_y;
	// float eyeZ = m_z;
	
	// float centerX = m_x + m_directionX;
	// float centerY = m_y + m_directionY;
	// float centerZ = m_z + m_directionZ;
	
	float upX = 0;
	float upY = 1;
	float upZ = 0;
	
	// vec3 forward = vec3(centerX - eyeX, centerY - eyeY, centerZ - eyeZ); - simplified now...
		
	// we already store centreX - eyeX as m_directionX

	glm::vec3 forward = glm::vec3(fDirectionX, fDirectionY, fDirectionZ);

	glm::vec3 up = glm::vec3(upX, upY, upZ);

	glm::vec3 forwardNormalised = glm::normalize(forward);
	
	//normalize(forward);
	glm::vec3 side = glm::vec3(forwardNormalised); // copy cross(forward, up, side);
	
	side = glm::cross(side, up);
	
	glm::vec3 sideNormalised = glm::normalize(side);
	
	//normalize(side);
	
	up = glm::vec3(sideNormalised);

	up = glm::cross(up, forwardNormalised); // no need to normalise as generated from 2 normalised vectors of unit length
		
										
	// now we build the matrix... (column major)

	// this is the transpose for the V matrix as Vinverse == VT for rotation matrices
	// row 0
		
	viewMatrix[0][0] = sideNormalised[0]; //0
	
	viewMatrix[1][0] = sideNormalised[1]; //4
	viewMatrix[2][0] = sideNormalised[2]; //8
	viewMatrix[3][0] = 0;
	
	//12
	// row 1
	
	viewMatrix[0][1] = up[0]; //1
	
	viewMatrix[1][1] = up[1]; //5
	
	viewMatrix[2][1] = up[2]; //9
	
	viewMatrix[3][1] = 0;
	
	//13
	// row 2
	
	viewMatrix[0][2] = -(forwardNormalised[0]); //2
	
	viewMatrix[1][2] = -(forwardNormalised[1]); //6
	
	viewMatrix[2][2] = -(forwardNormalised[2]); //10
	
	viewMatrix[3][2] = 0;
	
	//14
	// row 3
	
	viewMatrix[0][3] = 0; //3
	
	viewMatrix[1][3] = 0; //7

	viewMatrix[2][3] = 0;
	
	//11
	viewMatrix[3][3] = 1;
	
	//15
	// now apply translation to camera position
	glm::mat4 cameraTranslation = glm::translate(glm::mat4(1.0f), glm::vec3(-m_X, -m_Y, -m_Z));
	
	viewMatrix = viewMatrix * cameraTranslation; // pre or post multiply - - definitely POST!!!
}

//-------------------------------------------------------------------------------------------------

//! This will be used to prepare the direction vector.  
/*!
/
*/
void Camera::ComputeDirectionVector()
{
	float angleYZRadians = 3.14156f * fAngleYZ / 180.0f;
	
	fDirectionY = sin(angleYZRadians);
	
	float m_other = cos(angleYZRadians);
	float angleXZRadians = 3.14156f * fAngleXZ / 180.0f;
	
	fDirectionX = m_other * sin(angleXZRadians);
	fDirectionZ = m_other * -cos(angleXZRadians);
}

//-------------------------------------------------------------------------------------------------

//! This will be used to update the camera's current possition. 
/*!
/
*/
void Camera::UpdateCameraPosition(float distanceMoved)
{
	// later might use matrices to calculate this....
	// for now use angle in xz and stay on ground....
	// if moved update position

	m_X += distanceMoved * fDirectionX;
	m_Y += distanceMoved * fDirectionY;
	m_Z += distanceMoved * fDirectionZ;
}

//-------------------------------------------------------------------------------------------------

//! This will set the view matrix. 
/*!
/Param one : GLuint - Shader program. 
*/
void Camera::SetViewMatrix(GLuint program)
{
	Win32OpenGL::SendUniformMatrixToShader(program, viewMatrix, "view_matrix");
}

//-------------------------------------------------------------------------------------------------

//! This will check which key has been pressed and if it relates to the cameram controls. 
/*!
/Param one : char - key code (which key was pressed). 
*/
void Camera::HandleInput(unsigned char virtualKeyCode)
{
	float distanceMoved = 0.0f;

	float angleStep = 2.5f;

	if (virtualKeyCode == VK_LEFT)
	{
		fAngleXZ -= angleStep;
	}
	
	else if (virtualKeyCode == VK_RIGHT)
	{
		fAngleXZ += angleStep;
	}
	
	else if (virtualKeyCode == VK_UP)
	{
		distanceMoved = 0.1f;
	}
	
	else if (virtualKeyCode == VK_DOWN)
	{
		distanceMoved = -0.1f;
	}
	
	else if (virtualKeyCode == VK_PRIOR) //PAGEUP
	{
		fAngleYZ += angleStep;
	}
	
	else if (virtualKeyCode == VK_NEXT) //PAGEDOWN
	{
		fAngleYZ -= angleStep;
	}
	
	else if (virtualKeyCode == VK_ADD)
	{
		m_Y += 0.1f;
	}
	
	else if (virtualKeyCode == VK_SUBTRACT)
	{
		m_Y -= 0.1f;
	}
	
	// MORE KEY RESPONSES HERE: 
	
	
	// move camera and update view matrix
	
	ComputeDirectionVector();
	
	if (distanceMoved != 0.0f)
	{
		UpdateCameraPosition(distanceMoved);
	}
	
	ComputeViewMatrixUsingLookAt();

}

//-------------------------------------------------------------------------------------------------

