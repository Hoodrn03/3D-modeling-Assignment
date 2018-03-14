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

	std::fstream modelfile(sFilePath, std::ios_base::in);
	
	if (modelfile.is_open())
	{
		std::string line;

		while (getline(modelfile, line))
		{
			std::string s; 

			std::istringstream iss(line); 

			iss >> s; 

			if (s == "f")
			{
				


			}

			else if (s == "v")
			{



			}

		}

		modelfile.close();

	}


}

