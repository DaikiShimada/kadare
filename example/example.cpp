#include "../include/kadare/kadare.hpp"
#include <iostream>
#include <string>

int main(int argc, char* argv[])
{
	std::string data_file = "data/test_str_str.data";
	kadare::DataManager<std::string, std::string> x(data_file);

	// load data
	for (int i=0; i<x.getRecords(); ++i)
	{
		std::pair<std::vector<std::string>, std::vector<std::string> > d = x.load();
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
