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
	std::vector<float> v_IndexedVertices;
	
	// Vertex Texture
	std::vector<float> v_IndexedVertexTexture;

	// Vertex Normal
	std::vector<float> v_IndexedNormals; 

	// Faces 
	std::vector<unsigned int> v_FaceIndices;

	// Final Vector 
	std::vector<float> v_Vertices;

	// Member Functions 

public: 

	void m_loadobj(std::string sFilePath);

	std::vector<float> &m_GetVertices();

};
