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

	// Create an fstream item which will hold the current file being read. 
	std::fstream modelfile(sFilePath, std::ios_base::in);

	std::string sLine = ""; 

	// While the file is open. 
	if (modelfile.is_open())
	{
		while (getline(modelfile, sLine))
		{

			std::string s; 

			std::istringstream iss(sLine); 

			// Read the first Item: 
			iss >> s; 

			// If the first item is an 'f':
			if (s == "f")
			{

				// Check 'f' line 

				unsigned int iFaceIndex;

				static const int forwardSlash = 0x2F; 

				while (iss >> iFaceIndex)
				{

					iFaceIndex--;

					v_FaceIndices.push_back(iFaceIndex * 3);

				}

				// Construct vectors.

				for (int i = 0; i < 3; i++)
				{
					for (int j = 0; j < 3; j++)
					{
						v_Vertices.push_back(v_UnindexedVertices.at(v_FaceIndices.at(i) + j));
					}
				}
				
			
			v_FaceIndices.clear();


			}

			// If the first itemis an 'v':
			else if (s == "v")
			{

				// Check 'v' line

				float fVal;

				while (iss >> fVal)
				{
					// Add the value into the vector of vetices. 

					v_UnindexedVertices.push_back(fVal); 
				}

			}

			// If the first item is an 'vt':
			else if (s == "vt")
			{

				// Check 'vt' line 

				float fVal;

				while (iss >> fVal)
				{
					// Add the value into the vector of vertex textures. 

					v_UnindexedVertexTextures.push_back(fVal);
				}

			}

			// If the first item is an 'vn':
			else if (s == "vn")
			{

				// Check 'vn' line

				float fVal;

				while (iss >> fVal)
				{
					// Add the value into the vector of vertex normals. 

					v_UnindexedNormals.push_back(fVal);
				}

			}

		}

		// Close File 

		modelfile.close(); 
	}


}

//-------------------------------------------------------------------------------------------------

//! This will return the vertices for the final shape. 
/*!
/
*/
std::vector<float>& LoadObject::m_GetVertices()
{
	return v_Vertices; 
}

//-------------------------------------------------------------------------------------------------

//! This will return the vertex textures for the final shape. 
/*!
/
*/
std::vector<float>& LoadObject::m_GetVertexTextures()
{
	return v_VertexTextures;
}

//-------------------------------------------------------------------------------------------------

//! This will return the vertex normals for the final shape. 
/*!
/
*/
std::vector<float>& LoadObject::m_GetVertexNormals()
{
	return v_Normals; 
}

//-------------------------------------------------------------------------------------------------
