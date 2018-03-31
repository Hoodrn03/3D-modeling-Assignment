#pragma once

/*!\file LoadObject.h
*
* This class will be used to load objects from an obj file and 
* display it within the game world. 
*
*/

#include "Resource.h"
#include "defs.h"

class LoadObject
{
	// Constructor

public:

	LoadObject();



	// Deconstructor 

public:

	~LoadObject(); 



	// Data Members 

private:

	// Vertices 
	std::vector<float> v_UnindexedVertices;
	
	// Vertex Texture
	std::vector<float> v_UnindexedVertexTextures;

	// Vertex Normal
	std::vector<float> v_UnindexedNormals; 

	// Faces 
	std::vector<unsigned int> v_FaceIndices;

	// Final Vectors
	std::vector<float> v_Vertices;
	std::vector<float> v_VertexTextures;
	std::vector<float> v_Normals; 

	// Member Functions 

public: 

	// This will be used to load a model from an obj file. 
	void m_loadobj(std::string sFilePath);

	// This will be used to get access to the final set of vertices from the loaded object.
	std::vector<float> & m_GetVertices();

	// This will be used to get access to the final set of vertex textures from the loaded object.
	std::vector<float> & m_GetVertexTextures(); 

	// This will be used to get access to the final set of vertex normals from the loaded object.
	std::vector<float> & m_GetVertexNormals(); 

};
