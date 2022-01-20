// Designing Data-Intensive Applications by Kleppmann companion code
#include <iostream>
#include <string>

#include "Database.h"

int main()
{
	Database db;

	while (1)
	{
		// commands are of the form "set key value" or "get key"
		// keys cannot include spaces
		// value can include spaces so assume every char after 2nd space is value

		// could do this without creating new strings by pointing to line
		// TODO: don't create strings every loop while std::cin has all the info we need

		std::string line, key, value;

		getline(std::cin, line);

		// key begins after first space and ends right before second space
		// first space is always at 4
		// second space can be found with str::find and an offset
		std::size_t space_location = line.find(" ", 5);
		
		if (space_location != std::string::npos)
		{
			// if second space was found, pull out key with a substring
			// space_location - 4 gives length of substring
			key = line.substr(4, space_location - 4);
			// assign value to rest of cin and give it to db_set
			value = line.substr(space_location);
			db.db_set(key, value);
		}
		else
		{
			// if not, then just assign 4 until end for key and call db_get
			key = line.substr(4);
			db.db_get(key);
		}
	}
}