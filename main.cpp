#include "DataStorage.h"

#include <iostream>

#ifdef _WIN32 
#include <io.h>
#include <fcntl.h>
#endif 

using namespace DataSorters;

int main()
{
	setlocale(LC_ALL, "ru_RU.UTF-8");

#ifdef _WIN32
	_setmode(_fileno(stdout), _O_U16TEXT); 
	_setmode(_fileno(stdin), _O_U16TEXT); 
	_setmode(_fileno(stderr), _O_U16TEXT); 
#endif 
	
	std::wcout << L"Введите путь до файла:" << std::endl;
	std::wstring file_path;
	std::getline(std::wcin, file_path);
	
	try {
		DataStorage storage(file_path);
		int sort_type;
		while (true) {
			std::wcout << L"Для сортировки по именам введите – 1, по фамилиям введите- 2, по телефонам введите- 3" << std::endl;
			std::wcin >> sort_type;
			storage.sort(sort_type);
		}
	}
	catch (...) {

	}

	return 0;
}