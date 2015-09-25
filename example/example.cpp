#include "../include/kadare/kadare.hpp"
#include <string>

int main(int argc, char* argv[])
{
	std::string data_dir = "data";
	std::string data_file = "test_str_str.data";
	kadare::DataManager<std::string, std::string> x(data_dir, data_file);
	return 0;
}
