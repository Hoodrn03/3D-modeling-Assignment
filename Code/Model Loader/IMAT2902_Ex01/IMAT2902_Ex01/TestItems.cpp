/*!\file TestItems.cpp
*
* This will hold all of the function definitions for the class TestItems.
*
*/

#include "stdafx.h"
#include "TestItems.h"


//-------------------------------------------------------------------------------------------------

//! This is the Constructor for the Camera class. 
/*!
/
*/
TestItems::TestItems()
{

}

//-------------------------------------------------------------------------------------------------

//! This is the deconstructor for the Camera class. 
/*!
/
*/
TestItems::~TestItems()
{

}

//-------------------------------------------------------------------------------------------------

//! This will set the vertices needed to draw a 2D triangle. 
/*!
/
*/
void TestItems::m_CreateTriangle()
{
	float sourceVertices[] = {
		-0.5f,-0.5f,0,
		0.5f,-0.5f,0,
		-0.5f, 0.5f,0 };

	int numberOfElements = sizeof(sourceVertices) / sizeof(float);
	
	for (int i = 0; i < numberOfElements; i++)
	{
		m_vertices.push_back(sourceVertices[i]);
	}
}

//-------------------------------------------------------------------------------------------------

//! This will set the vertices needed to draw a 3D cube. 
/*!
/
*/
void TestItems::m_CreateCube()
{

	float cubeCoords[72] = {
		1,1,1,    -1,1,1,   -1,-1,1,   1,-1,1,      // face #1
		1,1,1,     1,-1,1,   1,-1,-1,  1,1,-1,      // face #2
		1,1,1,     1,1,-1,  -1,1,-1,  -1,1,1,       // face #3
		-1,-1,-1, -1,1,-1,   1,1,-1,   1,-1,-1,     // face #4
		-1,-1,-1, -1,-1,1,  -1,1,1,   -1,1,-1,      // face #5
		-1,-1,-1,  1,-1,-1,  1,-1,1,   -1,-1,1 };  // face #6


	int numberOfElements = sizeof(cubeCoords) / sizeof(float);

	for (int i = 0; i < numberOfElements; i++)
	{
		m_vertices.push_back(cubeCoords[i]);
	}
}

//-------------------------------------------------------------------------------------------------

//! This will allow access to the vertices of the recently created shape. 
/*!
/
*/
std::vector<float>& TestItems::m_GetVertices()
{
	return m_vertices;
}

//-------------------------------------------------------------------------------------------------
