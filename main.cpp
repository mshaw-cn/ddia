// Designing Data-Intensive Applications by Kleppmann companion code
#include <iostream>
#include <sstream>

#include "Database.h"



int main()
{
	Database db;

	while (1)
	{
		// make stringstream from std::cin
		std::string input;
		getline(std::cin, input);
		std::stringstream ss(input);

		// get token from beginning of stream
		std::string token;
		ss >> token;

		// switch on token (set/get)
		if (token == "set")
		{
			std::string key;
			std::string value;

			ss >> key;
			// extract the rest and assign to value
			// I'm sure there is a better way to extract the rest of the stream
			// TODO: Cleanup
			while (ss.good())
			{
				std::string temp;
				ss >> temp;
				value.append(" " + temp);
			}

			db.db_set(key, value);
		}
		else if (token == "get")
		{
			std::string key;
			ss >> key;

			db.db_get(key);
		}
	}
}