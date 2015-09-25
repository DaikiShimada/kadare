#include "../include/kadare/kadare.hpp"
#include <iostream>
#include <string>

int main(int argc, char* argv[])
{
	std::string data_file = "data/test_str_str.data";
	kadare::DataManager<std::string, std::string> dm(data_file);

	std::cout << "Input file name: " << dm.getDbfile() << std::endl;
	std::cout << "# of Records: " << dm.getRecords() << std::endl;
	std::cout << "Key dimension: " << dm.getKey_dim() << std::endl;
	std::cout << "Value dimension: " << dm.getValue_dim() << std::endl;

	// load data
	std::cout << "Data: " << std::endl;
	for (int i=0; i<dm.getRecords(); ++i)
	{
		std::pair<std::vector<std::string>, std::vector<std::string> > d = dm.load();
		std::vector<std::string>::iterator key_itr = d.first.begin();
		std::vector<std::string>::iterator value_itr = d.second.begin();
		
		for (key_itr=d.first.begin(); key_itr!=d.first.end(); ++key_itr)
			std::cout << *key_itr << " ";

		std::cout << "-> ";

		for (value_itr=d.second.begin(); value_itr!=d.second.end(); ++value_itr)
			std::cout << *value_itr << " ";

		std::cout << std::endl;
	}

	return 0;
}
