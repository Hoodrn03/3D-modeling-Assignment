#pragma once

/*!\file TestItems.h
*
* This class will be used to hold all of the test items for the program
* these will be used to check if the drawing functions are working correctly. 
*
*/

#include "defs.h"

class TestItems
{
	// Constructor 

public:

	TestItems();

	// Deconstructor 

public:

	~TestItems();

	// Data Members 

private:

	// This will hold the loaded test shape. 
	std::vector<float> v_Vertices;

	// Member Functions 

public:


	// This will be used to load the 2D triangle into vertices.
	void m_CreateTriangle();

	// This will be used to load the 3D cube into vertices.
	void m_CreateCube();

	// This will be used to get access to the vector containing the vertices. 
	std::vector<float> & m_GetVertices();

};