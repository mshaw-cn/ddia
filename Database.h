#pragma once
/*
	Class with two functions that implement a key-value store.
	You can call 'db_set key value' which will store 'key' and 'value' in the database.
	You can call 'db_get key' which looks up the most recent 'value' associated to that 'key' and returns it.
	The underlying storage format is a text file where each lines contains a 'key, value'.
	Every call to 'db_set' appends to the end of the file.

	Performance:
	let N = { n : n is an entry in the db }
	Initialization is O(N) as it creates m_hash_index on creation
	'db_set' is O(1) as its append only
	'db_get' is O(1) as it finds byte offset in m_hash_index and uses it to get value from that line in 'database'
*/

#include <iostream>
#include <fstream>
#include <unordered_map>

class Database
{
private:
	// I just guessed at initial size
	// TODO: Research proper size of byte offset
	std::unordered_map<std::string, uint16_t> m_hash_index;

public:
	Database()
	{
		get_hash_index();
	}

	int db_set(const std::string& key, const std::string& value)
	{
		// want to open up 'database' and append 'key, value'
		std::fstream file;

		file.open("database", std::fstream::app);
		
		file << key << ", ";

		// right before we commit value, lets get byte offset and update m_hash_index
		file.seekp(0, std::ios_base::end);

		file << value << std::endl;

		file.close();

		std::cout << "Set: " << key << " As: " << value << std::endl;
		return 0;
	}

	std::string db_get(const std::string& search_key)
	{
		std::string line_value = "";

		// check if search_key is in hash_index
		auto search = m_hash_index.find(search_key);
		if (search != m_hash_index.end())
		{
			std::fstream file;

			file.open("database", std::fstream::in);

			file.seekg(m_hash_index[search_key]);
			getline(file, line_value);

			file.close();
		}
		std::cout << "Found: " << line_value << std::endl;

		return line_value;
	}
private:
	void get_hash_index()
	{
		/* we want to update the m_hash_index where each key in the index relates to a byte offset
		of where the key can be found in the database. This will allow for O(1) search instead of O(n)
		provided that the hash_index can fit in memory.*/
		
		std::fstream file;
		file.open("database", std::fstream::in);
		
		// extract key from line using getline and the fact that the format is "key, value"
		std::string line_key;
		while (file.good())
		{
			getline(file, line_key, ' '); // extracts "key," or ""

			if (line_key == "")
				continue; 
			else 
			{
				line_key.pop_back(); // gets rid of ','
				m_hash_index[line_key] = uint16_t(file.tellg());
			}

			getline(file, line_key); // just moving to start of new line. probably a better way
		}
		file.close();
	}
};