#include "Song.h"
#include <sstream>

#define NO_TAG 0

Song::Song(const std::string& title, const std::string& tagsStr, const std::string& data,
		   const std::string& author, double bpm) :
	_title(title), _tags(), _data(), _author(author), _bpm(bpm)
{
	std::istringstream iss(tagsStr);
	int weight, i = 0;
	std::string result;
	while (iss.good())
	{
		i++;	   // Assuming the format is: <tag> <weight> <tag> <weight>...
		if (i % 2) // Checks if it is a tag or a weight
		{
			iss >> result;
		}
		else
		{
			iss >> weight;
			_tags.insert(std::pair<std::string, int>(result, weight));
		}
	}
	iss.clear();
	iss.str(data);
	while (iss.good())
	{
		iss >> result;
		_data.insert(result);
	}
}

Song::~Song()
{
}

int Song::hasTag(const std::string& tag) const
{
	TagsList::const_iterator foundTag = _tags.find(tag);
	if (foundTag == _tags.end())
	{
		return NO_TAG;
	}
	return (*foundTag).second;
}