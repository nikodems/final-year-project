#include "LoadDEM.h"

std::string operator+(std::string const &a, int b)
{
	std::ostringstream oss;

	oss << a << b;
	return oss.str();
}

LoadDEM::LoadDEM()
{
	//filePath_Drive = "H:\\AirSafe2018\\preprocessed-data\\os";

	filePath_Quality = "-low.dem";
}


LoadDEM::~LoadDEM()
{
}

void LoadDEM::SetFilePath(string filePath)
{
	filePath_Drive = filePath;
}

void LoadDEM::SetFileQuality(int demQual)
{
	if (demQual == 0)
	{
		filePath_Quality = "-high.dem";
	}
	else if (demQual == 1)
	{
		filePath_Quality = "-med.dem";
	}
	else if (demQual == 2)
	{
		filePath_Quality = "-low.dem";
	}
}

//Converts a float's endianess
//Converts float to char, then swaps it around
float LoadDEM::ReverseFloat(const float f)
{
	float returnFloat;

	char* floatToConvert = (char*)& f;
	char* returnValue = (char*)& returnFloat;

	returnValue[0] = floatToConvert[3];
	returnValue[1] = floatToConvert[2];
	returnValue[2] = floatToConvert[1];
	returnValue[3] = floatToConvert[0];

	return returnFloat;
}

std::vector<float> LoadDEM::OpenFile(XMINT3 path)
{
	std::ifstream infile;

	//Need to add a 0 to digits before 10
	if (path.z / 10 == 0)
	{
		//https://stackoverflow.com/questions/347132/append-an-int-to-char
		//Use stringstream to add strings and ints together
		stringstream ss;
		ss << filePath_Drive << "\\" << path.x << "\\" << path.y << "\\" << "0" << path.z << filePath_Quality;
		infile.open(ss.str(), std::ios::binary | std::ios::in);
	}
	else
	{
		stringstream ss;
		ss << filePath_Drive << "\\" << path.x << "\\" << path.y << "\\" << path.z << filePath_Quality;
		infile.open(ss.str(), std::ios::binary | std::ios::in);
	}

	//Go to end of file
	infile.seekg(0, infile.end);
	//Get file length
	const int length = infile.tellg() / 2;
	//Return to beginning
	infile.seekg(0, infile.beg);

	float* buffer;
	buffer = new float[length / sizeof(float)];

	std::vector<float> floatbuffer;
	floatbuffer.reserve(length / 2);

	//Read floats in to vector
	//Only read halfway into file, other half consists of normals
	while (infile.read(reinterpret_cast<char *>(buffer), sizeof(float)) && floatbuffer.size() < length / 4)
	{
		floatbuffer.push_back(ReverseFloat(*buffer));
	}

	std::ofstream myFile;

	//Close file
	infile.close();

	delete[] buffer;
	buffer = NULL;

	return floatbuffer;
}


//LOW - 26x26

//Dundee - 37/43