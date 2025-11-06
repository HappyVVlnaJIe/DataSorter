#include "DataStorage.h"
#include "DataSorter.h"

#include <fstream>
#include <iostream>
#include <codecvt>

namespace DataSorters {

	DataStorage::DataStorage(const fs::path& file_path) :r(L"([À-ß][à-ÿ]*)[ ]([À-ß][à-ÿ]*): ([0-9]+)") {
		if (!fs::exists(file_path)) {
			throw std::exception("Error: 'file doesn't exist'");
		}
		std::wifstream file(file_path);
		if (!file.is_open()) {
			throw std::exception("Error: 'can't open file'");
		}
		file.imbue(std::locale(std::locale::empty(), new std::codecvt_utf8<wchar_t>));
		std::wstring line;
		std::wsmatch m;
		while (!file.eof()) {
			std::getline(file, line);
			if (std::regex_search(line, m, r)) {
				if (m.size() == 4) {
					try {
						this->data.push_back({ m[1] ,m[2], std::stoull(m[3]) });
					}
					catch (const std::invalid_argument&) {
						std::wcout << L"Error: '" << m[3] << L"' is not a valid number" << std::endl;
					}
					catch (const std::out_of_range&) {
						std::wcout << L"Error: '" << m[3] << L"' is out of uint64_t range" << std::endl;
					}
				}
			}
		}
	}

	void DataStorage::sort(const int& sort_type) {
		//TODO: remove code duplication
		if (sort_type == sort_by_name) {
			DataSorter<std::wstring, std::wstring, uint64_t> data_sorter;
			for (auto& elem : this->data) {
				data_sorter.add(elem.name, elem.second_name, elem.phone);
			}
			std::wcout << data_sorter;
		}
		else if (sort_type == sort_by_second_name) {
			DataSorter<std::wstring, std::wstring, uint64_t> data_sorter;
			for (auto& elem : this->data) {
				data_sorter.add(elem.second_name, elem.name, elem.phone);
			}
			std::wcout << data_sorter;
		}
		else if (sort_type == sort_by_phone) {
			DataSorter<uint64_t, std::wstring, std::wstring> data_sorter;
			for (auto& elem : this->data) {
				data_sorter.add(elem.phone, elem.name, elem.second_name);
			}
			std::wcout << data_sorter;
		}
		else {
			throw std::exception("Error: 'non-existent sort type'");
		}
		
		////TODO: remove code duplication
		//switch (sort_type)
		//{
		//case sort_by_name:
		//	std::sort(data.begin(), data.end(), [](Person a, Person b) {
		//		return a.name.compare(b.name);
		//		});
		//	break;
	
		//case sort_by_second_name:
		//	std::sort(data.begin(), data.end(), [](Person a, Person b) {
		//		return a.second_name.compare(b.second_name);
		//		});
		//	break;

		//case sort_by_phone:
		//	std::sort(data.begin(), data.end(), [](Person a, Person b) {
		//		return a.phone > b.phone;
		//		});
		//	break;
		//default:
		//	break;
		//}
		
	}

}

