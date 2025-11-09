#include "InputReader.h"

#include <string>
#include <iostream>
#ifdef _WIN32 
#include <io.h>
#include <fcntl.h>
#endif 

InputReader::InputReader() :cur_state(InputState::file) {
	setlocale(LC_ALL, "ru_RU.UTF-8");

#ifdef _WIN32
	_setmode(_fileno(stdout), _O_U16TEXT);
	_setmode(_fileno(stdin), _O_U16TEXT);
	_setmode(_fileno(stderr), _O_U16TEXT);
#endif 
}

void InputReader::start() {
	std::wstring file_path, sort_type_str;
	int sort_type;
	while (true) {
		switch (cur_state)
		{
		case InputReader::InputState::file:
			std::wcout << L"ƒл€ завершени€ работы введите - -1" << std::endl;
			std::wcout << L"¬ведите путь до файла:" << std::endl;
			std::getline(std::wcin, file_path);

			if (file_path.compare(L"-1") == 0) {
				return;
			}
			try {
				storage = std::make_unique<DataSorters::DataStorage>(file_path);
				cur_state = InputState::sort_type;
			}
			catch (const std::wstring& e) {
				std::wcout << e << std::endl << std::endl;
			}
			catch (...) {
				std::wcout << "something went wrong" << std::endl;
				std::wcout << "please try again" << std::endl << std::endl;
			}
			break;

		case InputReader::InputState::sort_type:
			std::wcout << std::endl << L"ƒл€ сортировки по именам введите Ц 1, по фамили€м введите- 2, по телефонам введите- 3" << std::endl;
			std::wcout << L"ƒл€ смены файла введите - 0" << std::endl << std::endl;
			std::getline(std::wcin, sort_type_str);

			try	{
				sort_type = std::stoull(sort_type_str);
				if (sort_type == 0) {
					cur_state = InputState::file;
					continue;
				}
				if (sort_type == -1) {
					return;
				}
				storage->sort(sort_type);
			}
			catch (const std::invalid_argument&) {
				std::wcout << L"Error: '" << sort_type_str << L"' is not a valid number" << std::endl;
			}
			catch (const std::out_of_range&) {
				std::wcout << L"Error: '" << sort_type_str << L"' is out of range" << std::endl;
			}
			catch (const std::wstring& e) {
				std::wcout << e << std::endl << std::endl;
			}
			catch (...) {

			}
			break;
		}
	}
}
