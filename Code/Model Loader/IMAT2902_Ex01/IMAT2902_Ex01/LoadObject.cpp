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

				int iNumberOfValues = 0;

				std::string sTemp;

				while (iss >> sTemp)
				{

					// obj 'f' line def = 1/1/1 : v/vt/vn 

					// Used to check how many values are in the face line. 
					iNumberOfValues = 0;

					while (sTemp.size() != 0)
					{

						// Look for a '/' within the 'f' line
						int iPos = sTemp.find("/");

						// if there is a '/' within the face line: 
						if (iPos > 0)
						{
							iNumberOfValues++;

							// Create a string using a substring between the first char in the 'f' line up to the first occurance of '/'.

							std::string sCurrString = sTemp.substr(0, iPos);

							// Remove the characters from the beginning to the '/' including the '/'.
							sTemp.erase(0, iPos + 1);

							// Add the number(s) into the face index by converting them into an integer. 
							iFaceIndex = std::stoi(sCurrString);

							// Decrement it by one to make it corrospond to the correct value in the vector(s). 
							iFaceIndex--;

							// Add it to this set of FaceIndices. 
							v_FaceIndices.push_back(iFaceIndex);

							// reset the pos variable. 
							iPos = 0;
						}

						// If there are no '/'s within the line: 

						else
						{

							// Create a substring using the entire line. 

							std::string sCurrString = sTemp.substr(0, sTemp.size());

							// Delete the line. 

							sTemp.erase(0, sTemp.size());

							// Add the number(s) into the face index by converting them into an integer. 

							iFaceIndex = std::stoi(sCurrString);

							// Decrement it by one to make it corrospond to the correct value in the vector(s). 

							iFaceIndex--;

							// Add it to this set of FaceIndices. 

							v_FaceIndices.push_back(iFaceIndex);
						}
					}
				}

				// Only a single set of values  f 1 2 3

				if (iNumberOfValues == 0)
				{
					for (int i = 0; i < 3; i += 1)
					{
						// Create the final vector using the current face index. 

						v_Vertices.push_back(v_UnindexedVertices.at(v_FaceIndices.at(i)));
					}
				}

				// Two sets of values  f 1/1 2/2 3/3

				else if (iNumberOfValues == 1)
				{
					for (int i = 0; i < 6; i += 2)
					{
						// Create the two final vectors using the current face index. 

						v_Vertices.push_back(v_UnindexedVertices.at(v_FaceIndices.at(i)));
						
						v_Normals.push_back(v_UnindexedNormals.at(v_FaceIndices.at(i + 1)));
					}
				}

				// Three sets of values f 1/1/1 2/2/2 3/3/3

				else if (iNumberOfValues == 2)
				{
					for (int i = 0; i < 9; i += 3)
					{
						// Create the three final vectors using the current face index. 

						v_Vertices.push_back(v_UnindexedVertices.at(v_FaceIndices.at(i)));
						
						v_VertexTextures.push_back(v_UnindexedVertexTextures.at(v_FaceIndices.at(i + 1)));
						
						v_Normals.push_back(v_UnindexedNormals.at(v_FaceIndices.at(i + 2)));
					}
				}

				// Clear this line of face indices. 

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
