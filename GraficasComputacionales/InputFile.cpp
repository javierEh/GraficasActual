#include "InputFile.h"
#include <fstream>
#include <iostream>
#include <sstream> 
using namespace std;

bool InputFile::Read(const std::string& filename)
{
	if (filename.empty())
	{
		std::cout << "No filemname provided" << std::endl;
		return false;
	}

	std::fstream inputFile(filename, std::fstream::in);

	if (!inputFile.is_open())
	{
		std::cout << "Could not open file" << filename << std::endl;
		return false;
	}

	std::stringstream ss;
	ss << inputFile.rdbuf();
	_contents = ss.str();

	//std::cout << _contents << filename << std::endl;
	return true;
}

const std::string InputFile::GetContents() const
{
	return _contents;
}

