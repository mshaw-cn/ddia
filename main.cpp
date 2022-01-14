// Designing Data-Intensive Applications by Kleppmann companion code
#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdlib> // for exit function


// inspired from page 70: Data Structures That Power Your Database
int db_set(std::string key, std::string value)
{
	// need to write the two strings separated by commas to disk
	std::ofstream outdata;
	outdata.open("database", std::ios::app);
	if (!outdata)
	{
		std::cerr << "Error: file could not be opened" << std::endl;
		exit(1);
	}
	outdata << key << ", " << value << std::endl;
	outdata.close();

	return 1;
}

int db_get(std::string key)
{
	std::string line_string;

	std::ifstream indata;
	indata.open("database", std::ios::out);
	if (!indata)
	{
		std::cerr << "Error: file could not be opened" << std::endl;
		exit(1);
	}

	// find last (closest to bottom) key in file and print value to console
	std::string l_value;
	while (indata)
	{
		getline(indata, line_string);
		if (line_string == "")
		{
			l_value.pop_back();
			std::cout << l_value << std::endl;
			return 1;
		}
		std::stringstream ss(line_string);
		
		std::string l_key;
		ss >> l_key; 
		l_key.pop_back(); // gets rid of comma

		if (l_key == key) 
		{
			l_value = "";
			while (ss.good())
			{
				std::string temp;
				ss >> temp;
				l_value.append(temp + " ");
			}
		}
	}

	return 1;
}

int main()
{
	while (1)
	{
		std::string input;
		getline(std::cin, input);
		std::stringstream ss(input);

		std::string token;
		ss >> token;

		if (token == "set")
		{
			// should probably have some check to make sure the key and value are present
			std::string key;
			std::string value;
			ss >> key;
			while (ss.good())
			{
				std::string temp;
				ss >> temp;
				value.append(" " + temp);
			}

			db_set(key, value);
		}
		else if (token == "get")
		{
			std::string key;
			ss >> key;

			db_get(key);
		}
	}
}