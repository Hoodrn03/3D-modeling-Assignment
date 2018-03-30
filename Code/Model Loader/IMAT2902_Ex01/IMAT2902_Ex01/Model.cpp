/*!\file Model.cpp
*
* This will hold all of the function definitions for the class Model.
*
*/

#include "stdafx.h"
#include "Model.h"


//-------------------------------------------------------------------------------------------------

//! This is the Constructor for the Model class. 
/*!
/
*/
Model::Model()
{

}

//-------------------------------------------------------------------------------------------------

//! This is the Deconstructor for the Model class. 
/*!
/
*/
Model::~Model()
{

}


//-------------------------------------------------------------------------------------------------

//! This will load a model from an obj file. 
/*!
/Param One : String - The string is for the file path to find the obj file for the model to load. 
*/
void Model::m_LoadModel(std::string sFilePath)
{
	m_loadObject.m_loadobj(sFilePath);

}


//-------------------------------------------------------------------------------------------------

//! This will load a model from an obj file. 
/*!
/Param One : String - The string is for the file path to find the obj file for the model to load.
*/
void Model::m_PrepareModel()
{
	// later we can use Win32OpenGL::CreateVAO(m_vao, m_vboVertices, vertices);
	// create the vertex buffer object - the vbo

	// Vertices :

	glGenBuffers(1, &m_vboVertices);
	glBindBuffer(GL_ARRAY_BUFFER, m_vboVertices);
	glBufferData(GL_ARRAY_BUFFER, m_loadObject.m_GetVertices().size() * sizeof(GLfloat), &m_loadObject.m_GetVertices()[0], GL_STATIC_DRAW);

	// Normals 

	glGenBuffers(1, &m_vboNormals);
	glBindBuffer(GL_ARRAY_BUFFER, m_vboNormals);
	glBufferData(GL_ARRAY_BUFFER, m_loadObject.m_GetVertexNormals().size() * sizeof(GLfloat), &m_loadObject.m_GetVertexNormals()[0], GL_STATIC_DRAW);

	// create the vertex array object - the vao
	
	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);
	// Vertices 
	glBindBuffer(GL_ARRAY_BUFFER, m_vboVertices);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
	// Normals 
	glBindBuffer(GL_ARRAY_BUFFER, m_vboNormals);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	// vertices are element 0 in VAO (the only element currently).
	glEnableVertexAttribArray(0);

	// Normals element 1. 
	glEnableVertexAttribArray(1);
}


//-------------------------------------------------------------------------------------------------

//! This will load a model from an obj file. 
/*!
/Param One : String - The string is for the file path to find the obj file for the model to load.
*/
void Model::m_DrawModels()
{
	glBindVertexArray(m_vao); // select first VAO
	
	GLuint numberOfElements = m_loadObject.m_GetVertices().size() / 3;
	
	glDrawArrays(GL_TRIANGLES, 0, numberOfElements); // draw first object
	
	glBindVertexArray(0);
}



