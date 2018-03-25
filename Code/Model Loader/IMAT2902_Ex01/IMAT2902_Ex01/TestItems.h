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

	std::vector<float> m_vertices;

	// Member Functions 

public:


	void m_CreateTriangle();

	void m_CreateCube();

	std::vector<float> & m_GetVertices();

};