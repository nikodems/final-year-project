#ifndef _LOADDEM_H
#define _LOADDEM_H

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <ios>
#include <string>

#include "DEMPlane.h"

class LoadDEM
{
public:
	LoadDEM();
	~LoadDEM();

	float ReverseFloat(const float f);

	std::vector<float> OpenFile(XMINT3 path);

	void SetFilePath(std::string filePath);
	void SetFileQuality(int demQual);
private:
	
	std::string filePath_Drive;
	std::string filePath_Quality;

	
}; 
#endif



