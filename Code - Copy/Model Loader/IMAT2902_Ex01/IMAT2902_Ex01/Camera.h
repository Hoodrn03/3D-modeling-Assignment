#pragma once

/*!\file Camera.h
*
* This class will be used to handle the camera, it will allow for it to be moved
* and rotated. 
*
* The Camera's main job is to allow for the view to change.  
*
*/

#include "defs.h"

class Camera
{
	// Constructor 

public:

	Camera();

	// Deconstructor

public:
	
	~Camera();

	// Data Members 

private:

	// Set the starting values. 
	const float fStartX = 0, fStartY = 1.5f, fStartZ = 5; 

	// Assign the current values to the starting values upon creation.
	float m_X{ fStartX };
	float m_Y{ fStartY };
	float m_Z{ fStartZ };

	// Create variables which will hold the camera's angle. 
	float fAngleXY{ 0 };
	float fAngleXZ{ 0 };
	float fAngleYZ{ 0 };

	// Create variables which will hold the camera's direction. 
	float fDirectionX{ 0 };
	float fDirectionY{ 0 };
	float fDirectionZ{ 0 };

	// This is the final view matrix which will be updated. 
	glm::mat4 viewMatrix; 

	// Member Functions 

public:

	void ComputeViewMatrixUsingLookAt();

	void ComputeDirectionVector();

	// This will be used to update the camera's current possition after one of the movement keys has been pressed. 
	void UpdateCameraPosition(float distanceMoved);

	void SetViewMatrix(GLuint program);

	// This will be used to check if a certain key relating to the camera movement has been pressed. 
	void HandleInput(unsigned char virtualKeyCode);

};