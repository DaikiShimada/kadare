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

template<typename T>
T lexical_cast(const std::string &src)
{
	T dst;
	std::istringstream(src) >> dst;
	return dst;
}


template<typename T>
std::vector<T> split(const std::string& str, char delim)
{
	std::vector<T> splited;
	int cur = 0;
	int found;

	while ((found=str.find_first_of(delim, cur)) != std::string::npos)
	{
		splited.push_back(lexical_cast<T>(std::string(str, cur, found-cur)));
		cur = found + 1;
	}

	splited.push_back(lexical_cast<T>(std::string(str, cur, str.size()-cur)));
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

template<typename Key_type, typename Value_type>
DataManager<Key_type, Value_type>::DataManager(const DataManager<Key_type, Value_type>& obj)
{
	this->dbfile = obj.getDbfile();
	this->dbdir = obj.getDbdir();
	this->cur = obj.getCur();
	this->records = obj.getRecords();
	this->key_dim = obj.getKey_dim();
	this->value_dim = obj.getValue_dim();
}

template<typename Key_type, typename Value_type>
DataManager<Key_type, Value_type>::DataManager(const std::string& dbdir, const std::string& dbfile)
{
	setDbdir(dbdir);
	setDbfile(dbfile);
}

template<typename Key_type, typename Value_type>
DataManager<Key_type, Value_type>::~DataManager()
{
	/* nop */
}

template<typename Key_type, typename Value_type>
void DataManager<Key_type, Value_type>::setDbfile(const std::string& dbfile)
{
	this->dbfile = dbfile;
	std::ifstream ifs(dbdir + "/" + dbfile);
	cur = 0;

	// read header
	readHeader();

	// get lines
	records = key.size();
}

template<typename Key_type, typename Value_type>
void DataManager<Key_type, Value_type>::setDbfile(const std::string& dbdir, const std::string& dbfile)
{
	setDbdir(dbdir);
	setDbfile(dbfile);
}

template<typename Key_type, typename Value_type>
void DataManager<Key_type, Value_type>::setDbdir(const std::string& dbdir)
{
	this->dbdir = dbdir;
}

template<typename Key_type, typename Value_type>
void DataManager<Key_type, Value_type>::load()
{
	cur++;
	if (cur >= records)
	{	// back to begining
		cur = 0;
	}
	key_data = key[cur];
	value_data = value[cur];
}

template<typename Key_type, typename Value_type>
void DataManager<Key_type, Value_type>::readHeader()
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
			std::vector<std::string> header = split<std::string>(buf, ',');		
			key_dim = std::atoi(header[1].c_str());
			value_dim = std::atoi(header[2].c_str());

			hasHeader = true;
		}
		else if (hasHeader)
		{
			// contents
			std::vector<std::string> content = split<std::string>(buf, '\t');
			key.push_back(split<Key_type>(content[0], ','));
			value.push_back(split<Value_type>(content[1], ','));
		}

		std::getline(ifs, buf);
	}
	ifs.close();
}
}
