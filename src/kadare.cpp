#include <cstdlib>
#include <kadare/kadare.hpp>

namespace kadare{

/*
	String Util
*/

void deleteSpace(std::string& buf)
{
	int pos;
	while ((pos=buf.find_first_of(" 　\t")) != std::string::npos)
	{
		buf.erase(pos, 1);
	}
}

std::vector<std::string> split(const std::string& str, char delim)
{
	std::vector<std::string> splited;
	int cur = 0;
	int found;

	while ((found=str.find_first_of(delim, cur)) != std::string::npos)
	{
		splited.push_back(std::string(str, cur, found-cur));
		cur = found + 1;
	}

	splited.push_back(std::string(str, cur, str.size()-cur));
	return splited;
}

template<typename Key_type, typename Value_type>
DataManager<Key_type, Value_type>::DataManager()
{
	cur = 0;
	records = 0;
	key_dim = 0;
	value_dim = 0;
	dbfile = "";
	dbdir = "./";
}

DataManager::DataManager(const DataManager& obj)
{
	this->dbfile = obj.getDbfile();
	this->dbdir = obj.getDbdir();
	this->cur = obj.getCur();
	this->records = obj.getRecords();
	this->key_dim = obj.getKey_dim();
	this->value_dim = obj.getValue_dim();
}

DataManager::DataManager(const std::string& dbdir, const std::string& dbfile)
{
	setDbdir(dbdir);
	setDbfile(dbfile);
}

DataManager::~DataManager()
{
	/* nop */
}

void DataManager::setDbfile(const std::string& dbfile)
{
	this->dbfile = dbfile;
	std::ifstream ifs(dbdir + "/" + dbfile);
	cur = 0;

	// read header
	readHeader();

	// get lines
	records = key.size();
}

void DataManager::setDbfile(const std::string& dbdir, const std::string& dbfile)
{
	setDbdir(dbdir);
	setDbfile(dbfile);
}

void DataManager::setDbdir(const std::string& dbdir)
{
	this->dbdir = dbdir;
}

void DataManager::load()
{
	cur++;
	if (cur >= records)
	{	// back to begining
		cur = 0;
	}
	key_data = key[cur];
	value_data = value[cur];
}

void DataManager::readHeader()
{
	std::ifstream ifs(dbdir + "/" + dbfile);
	bool hasHeader = false;

	std::string buf;
	std::getline(ifs, buf);

	while (!ifs.eof())
	{
		if (buf[0] == '@')
		{
			// header
			std::vector<std::string> header = split(buf, ',');		
			key_dim = std::atoi(header[1].c_str());
			value_dim = std::atoi(header[2].c_str());

			hasHeader = true;
		}
		else if (hasHeader)
		{
			// contents
			std::vector<std::string> content = split(buf, '\t');
			key.push_back(split(content[0], ','));
			value.push_back(split(content[1], ','));
		}

		std::getline(ifs, buf);
	}
	ifs.close();
}
}
