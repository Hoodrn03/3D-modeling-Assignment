/*!\file LoadObject.cpp
*
* This will hold all of the function definitions for the class LoadObject. 
*
*/

#include "stdafx.h"
#include "LoadObject.h"


//-------------------------------------------------------------------------------------------------

//! This is the constructor for the load object class
/*!
/
*/
LoadObject::LoadObject()
{

}

//-------------------------------------------------------------------------------------------------

//! This is the deconstructor for the load object class
/*!
/
*/
LoadObject::~LoadObject()
{

}

//-------------------------------------------------------------------------------------------------

//! This will be used to load an obj file. 
/*!
/Param one : A string which will hold the file path for the model which will be loaded. 
*/
void LoadObject::m_loadobj(std::string sFilePath)
{




}


//! This will return the final vertex for the shape, allowing for it to be drawn. 
/*!
/
*/
std::vector<float>& LoadObject::m_GetVertices()
{
	return v_Vertices; 
}




