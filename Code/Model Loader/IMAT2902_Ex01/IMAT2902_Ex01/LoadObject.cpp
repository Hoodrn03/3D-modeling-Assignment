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

	std::string line = ""; 

	if (modelfile.is_open())
	{
		while (getline(modelfile, line))
		{

			std::string s; 

			std::istringstream iss(line);

			iss >> s; 

			if (s == "f")
			{

				// Check 'f' line 

				unsigned int iFaceIndex; 

				while (iss >> iFaceIndex)
				{
					iFaceIndex--; 

					v_FaceIndices.push_back(iFaceIndex * 3); 
				}

			}

			else if (s == "v")
			{

				// Check 'v' line

				for (int i = 0; i < 3; i++)
				{
					float val; 

					iss >> val; 

					v_IndexedVertices.push_back(val); 
				}

			}

			else if (s == "vt")
			{

				// Check 'vt' line 

				for (int i = 0; i < 2; i++)
				{
					float val;

					iss >> val;

					v_IndexedVertexTexture.push_back(val);
				}

			}

			else if (s == "vn")
			{

				// Check 'vn' line

				for (int i = 0; i < 3; i++)
				{
					float val;

					iss >> val;

					v_IndexedNormals.push_back(val);
				}

			}

			

		}

		// Close File 

		modelfile.close(); 
	}

	// Create Final Vector. 


}


//! This will return the final vertex for the shape, allowing for it to be drawn. 
/*!
/
*/
std::vector<float>& LoadObject::m_GetVertices()
{
	return v_Vertices; 
}




