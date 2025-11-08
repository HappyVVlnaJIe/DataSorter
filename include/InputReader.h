#pragma once 

#include "DataStorage.h"

#include <memory>

class InputReader {
public:
	InputReader();
	void start();
private:
	std::unique_ptr<DataSorters::DataStorage> storage;
	enum class InputState {
		file,
		sort_type
	};
	InputState cur_state;
};