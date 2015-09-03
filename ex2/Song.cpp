#include "Song.h"
#include <sstream>

#define NO_TAG 0

Song::Song(std::string title, std::string tagsStr, std::string data, 
		   std::string author, double bpm = NO_BPM) :
	_title(title), _author(author), _bpm(bpm), _tags(), _data()
{
	std::istringstream iss(tagsStr);
	int weight, i = 0;
	std::string result;
	while (iss.good())
	{
		i++;
		if (i % 2)
		{
			iss >> result;
		}
		else
		{
			iss >> weight;
			_tags.insert(std::pair<std::string, int>(result, weight));
		}
	}
	iss = std::istringstream(data);
	while (iss.good())
	{
		iss >> result;
		_data.insert(result);
	}
}

Song::~Song()
{
}

int Song::hasTag(std::string tag) const
{
	std::unordered_map<std::string, int>::const_iterator foundTag = _tags.find(tag);
	if (foundTag == _tags.end)
	{
		return NO_TAG;
	}
	return (*foundTag).second;
}