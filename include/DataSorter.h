#pragma once

#include <iostream>
#include <map>
#include <type_traits>

namespace DataSorters {

	template<typename Key, typename First, typename Second>
	class DataSorter {
	public:
		void add(const Key& key, const First& first, const Second& second);
		template<typename Key, typename First, typename Second>
		friend std::wostream& operator<<(std::wostream& os, const DataSorter<Key, First, Second>& data_sorter);
	private:
		std::multimap<Key, std::pair<First, Second>> data;
	};

	template<typename Key, typename First, typename Second>
	inline void DataSorter<Key, First, Second>::add(const Key& key, const First& first, const Second& second) {
		data.insert({ key, { first, second } });
	}

	template<typename Key, typename First, typename Second>
	std::wostream& operator<<(std::wostream& os, const DataSorter<Key, First, Second>& data_sorter) {
		for (auto& line : data_sorter.data) {
			os << line.first;
			if (std::is_integral_v<Key>) {
				os << ": " << line.second.first << " " << line.second.second;
			}
			else {
				os << " " << line.second.first << ": " << line.second.second;
			}
			os << std::endl;
		}
		return os;
	}

}