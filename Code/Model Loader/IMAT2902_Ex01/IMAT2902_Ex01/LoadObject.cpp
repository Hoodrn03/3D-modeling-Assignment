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

				std::string temp;

				while (iss >> temp)
				{

					while (temp.size() != 0)
					{

						int pos = temp.find("/");

						if (pos > 0)
						{
							std::string currString = temp.substr(0, pos);

							temp.erase(0, pos + 1);

							iFaceIndex = std::stoi(currString);

							iFaceIndex--;

							v_FaceIndices.push_back(iFaceIndex);

							pos = 0;
						}

						else
						{
							std::string currString = temp.substr(0, temp.size());

							temp.erase(0, temp.size());

							iFaceIndex = std::stoi(currString);

							iFaceIndex--;

							v_FaceIndices.push_back(iFaceIndex);
						}
					}
				}



				v_Vertices.push_back(v_UnindexedVertices[v_FaceIndices[0]]);
				v_VertexTextures.push_back(v_UnindexedVertexTexture[v_FaceIndices[1]]);
				v_Normals.push_back(v_UnindexedNormals[v_FaceIndices[2]]);
				
				v_Vertices.push_back(v_UnindexedVertices[v_FaceIndices[3]]);
				v_VertexTextures.push_back(v_UnindexedVertexTexture[v_FaceIndices[4]]);
				v_Normals.push_back(v_UnindexedNormals[v_FaceIndices[5]]);

				v_Vertices.push_back(v_UnindexedVertices[v_FaceIndices[6]]);
				v_VertexTextures.push_back(v_UnindexedVertexTexture[v_FaceIndices[7]]);
				v_Normals.push_back(v_UnindexedNormals[v_FaceIndices[8]]);

				v_FaceIndices.clear();
				

			}

			else if (s == "v")
			{

				// Check 'v' line

				float val;

				while (iss >> val)
				{

					v_UnindexedVertices.push_back(val); 
				}

			}

			else if (s == "vt")
			{

				// Check 'vt' line 

				float val;

				while (iss >> val)
				{

					v_UnindexedVertexTexture.push_back(val);
				}

			}

			else if (s == "vn")
			{

				// Check 'vn' line

				float val;

				while (iss >> val)
				{

					v_UnindexedNormals.push_back(val);
				}

			}

			

		}

		// Close File 

		modelfile.close(); 
	}


}


//! This will return the final vertex for the shape, allowing for it to be drawn. 
/*!
/
*/
std::vector<float>& LoadObject::m_GetVertices()
{
	return v_Vertices; 
}

std::vector<float>& LoadObject::m_GetVTVertexes()
{
	return v_VertexTextures;
}

std::vector<float>& LoadObject::m_GetVNormals()
{
	return v_Normals; 
}




