#pragma once

#include <filesystem>
#include <string>
#include <vector>
#include <regex>
#include <unordered_map>
#include <functional>

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
		std::vector<int> sort_data(const int& sort_type);
		void create_sort_types();
		void output_sorted_data(const int& sort_type);
		struct Person	{
			std::wstring second_name;
			std::wstring name;
			uint64_t phone;
		};
		std::vector<Person> data;
		std::unordered_map<int, std::vector<int>> sorted_data_by_type;
		const std::wregex r;
		std::unordered_map<int, std::function<bool(const int&, const int&)>> sort_types;
	};
}