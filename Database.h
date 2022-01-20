#pragma once
/*
	Class with two functions that implement a key-value store.
	You can call 'db_set key value' which will store 'key' and 'value' in the database.
	You can call 'db_get key' which looks up the most recent 'value' associated to that 'key' and returns it.
	The underlying storage format is a text file where each lines contains a 'key, value'.
	Every call to 'db_set' appends to the end of the file.

	Performance:
	let N = { n : n is an entry in the db }
	'db_set' is O(1) as its append only
	'db_get' is O(N) as it must go through all elements to find most recent
*/

#include <iostream>
#include <fstream>

class Database
{
public:
	int db_set(const std::string& key, const std::string& value)
	{
		// want to open up 'database' and append 'key, value'
		std::fstream file;

		file.open("database", std::fstream::app);
		file << key << ", " << value << std::endl;
		file.close();

		std::cout << "Set: " << key << " As: " << value << std::endl;
		return 0;
	}

	std::string db_get(const std::string& search_key)
	{
		std::fstream file;
		std::string line_key, line_value;
		std::string latest_value = " "; // initialize in case key is not found

		file.open("database", std::fstream::in);
		while (file.good())
		{
			getline(file, line_key, ' '); // split at the first space because keys cannot have spaces

			if (line_key == "") // the last line is blank and will be assigned to line_key at the end of file
				continue; // so skip the rest to make file.bad()
			else
				line_key.pop_back();

			// get the rest of the line with the default \n delimiter
			getline(file, line_value);

			// for some reason there is a space char at the front of line_value so
			line_value.erase(0, 1);

			// compare keys and update line_value if match
			if (line_key == search_key)
				latest_value = line_value;
		}

		std::cout << "Latest: " << latest_value << std::endl;
		return latest_value;
	}
};