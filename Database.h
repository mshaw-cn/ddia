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

class Database
{
public:
	int db_set(std::string key, std::string value)
	{
		std::cout << "Set: " << key << " As: " << value << std::endl;
		return 1;
	}

	std::string db_get(std::string key)
	{
		return "";
	}
};