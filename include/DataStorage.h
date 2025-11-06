#pragma once

#include <filesystem>
#include <string>
#include <vector>
#include <regex>

namespace fs = std::filesystem;

namespace DataSorters {
	const int sort_by_name = 1;
	const int sort_by_second_name = 2;
	const int sort_by_phone = 3;

	class DataStorage {
	public:
		DataStorage(const fs::path& file_path);
		void sort(const int& sort_type);
	private:
		struct Person	{
			std::wstring second_name;
			std::wstring name;
			uint64_t phone;
		};
		std::vector<Person> data;
		const std::wregex r;
	};

}