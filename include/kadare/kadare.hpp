#ifndef KANTOKU_DATABASE_READER
#define KANTOKU_DATABASE_READER

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

namespace kadare{

void deleteSpace(std::string& buf);
std::vector<std::string> split(const std::string& str, char delim);

class DataManager
{
public:
	std::vector<std::vector<std::string> > key;
	std::vector<std::vector<std::string> > value;
	std::vector<std::string> key_data;
	std::vector<std::string> value_data;

	DataManager();
	DataManager(const std::string& dbdir, const std::string& dbfile);
	DataManager(const DataManager& obj);
	~DataManager();

	void load();
	void readHeader();

	const std::string getDbfile() const {return dbfile;}
	const std::string getDbdir() const {return dbdir;}
	const int getCur() const {return cur;}
	const int getRecords() const {return records;}
	const int getKey_dim() const {return key_dim;}
	const int getValue_dim() const {return value_dim;}

	void setDbfile(const std::string& dbfile);			
	void setDbfile(const std::string& dbdir, const std::string& dbfile);			
	void setDbdir(const std::string& dbdir);			
private:
	std::string dbfile;
	std::string dbdir;
	int cur;
	int records;
	int key_dim;
	int value_dim;
};

}
#endif
