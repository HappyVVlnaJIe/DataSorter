#include "DataStorage.h"

#include <fstream>
#include <iostream>
#include <codecvt>
#include <numeric>

namespace DataSorters {

	DataStorage::DataStorage(const fs::path& file_path) :
		r(L"([À-ß][à-ÿ]*)[ ]([À-ß][à-ÿ]*): ([0-9]+)")
	{
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
		create_sort_types();
	}

	void DataStorage::sort(const int& sort_type) {
		if (sort_types.contains(sort_type)) {
			if (!sorted_data_by_type.contains(sort_type)) {
				sorted_data_by_type[sort_type] = sort_data(sort_type);
			}
		}
		else {
			throw std::exception("Error: 'non-existent sort type'");
		}
		output_sorted_data(sort_type);
	}

	std::vector<int> DataStorage::sort_data(const int& sort_type) {
		std::vector<int> sorted_data;
		sorted_data.resize(data.size());
		std::iota(sorted_data.begin(), sorted_data.end(), 0);
		std::sort(sorted_data.begin(), sorted_data.end(), sort_types[sort_type]);
		return sorted_data;
	}

	void DataStorage::create_sort_types() {
		sort_types[sort_by_name] = [this](int lhs, int rhs) {
			return data[lhs].name.compare(data[rhs].name) < 0;
			};

		sort_types[sort_by_second_name] = [this](int lhs, int rhs) {
			return data[lhs].second_name.compare(data[rhs].second_name) < 0;
			};

		sort_types[sort_by_phone] = [this](int lhs, int rhs) {
			return data[lhs].phone < data[rhs].phone;
			};
	}

	void DataStorage::output_sorted_data(const int& sort_type) {
		switch (sort_type)
		{
		case sort_by_name:
			for (auto& indx : sorted_data_by_type[sort_by_name]) {
				std::wcout << data[indx].name << L" " << data[indx].second_name << L": " << data[indx].phone << std::endl;
			}
			break;

		case sort_by_second_name:
			for (auto& indx : sorted_data_by_type[sort_by_second_name]) {
				std::wcout << data[indx].second_name << L" " << data[indx].name << L": " << data[indx].phone << std::endl;
			}
			break;

		case sort_by_phone:
			for (auto& indx : sorted_data_by_type[sort_by_phone]) {
				std::wcout << data[indx].phone << L": " << data[indx].name << L" " << data[indx].second_name << std::endl;
			}
			break;
		default:
			break;
		}
	}
}

