#include "InputReader.h"

#include <iostream>

#ifdef _WIN32 
#include <io.h>
#include <fcntl.h>
#endif 

using namespace DataSorters;

int main()
{
	InputReader reader;
	reader.start();
	return 0;
}