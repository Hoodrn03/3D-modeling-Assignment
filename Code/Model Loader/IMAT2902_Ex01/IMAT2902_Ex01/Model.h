#pragma once

/*!\file TestItems.h
*
* This class will be used to hold the currently loaded model. 
*
*/

#include "defs.h"
#include "LoadObject.h"

class Model
{
	// Constructor 

public:

	Model();

	// Deconstructor 

public:

	~Model();

	// Data Members 

private:

	LoadObject m_loadObject;

	GLuint m_vao;

	GLuint m_vboVertices;
	GLuint m_vboNormals; 

	// Member Functions 

public:

	void m_LoadModel(std::string sFilePath);

	void m_PrepareModel();

	void m_DrawModels();

};
