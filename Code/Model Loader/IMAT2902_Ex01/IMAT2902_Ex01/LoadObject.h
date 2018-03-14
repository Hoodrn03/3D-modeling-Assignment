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

	std::vector<std::string> valuesX;
	std::vector<std::string> valuesY;
	std::vector<std::string> valuesZ;

	// Member Functions 

public: 

	void m_loadobj(std::string sFilePath);

};
