#include "Song.h"
#include <sstream>

#define NO_TAG 0

/**
 * Constructor for a song object (abstract).
 * @param title The song's title
 * @param tagsStr A list of tags and their weight separated by spaces - <tag> <weight> ...
 * @param data The data for this song separated by spaces.
 * @param author The author of this song (lyrics , performer)
 * @param bpm The bpm value of this song ( default is NO_BPM (0.0) )
 */
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
		if (result.size() > 0)
		{
			_data.insert(result);
		}
	}
}

/**
 * No special details for destructor.
 */
Song::~Song()
{
}

/**
* Checks if this song has a given tag. If so, returns its value (weight).
* Otherwise, returns 0.
* @param tag The string of a tag to check.
* @return The weight of the given tag if this songs contains it, 0 otherwise.
*/
int Song::hasTag(const std::string& tag) const
{
	TagsList::const_iterator foundTag = _tags.find(tag);
	if (foundTag == _tags.end())
	{
		return NO_TAG;
	}
	return foundTag->second;
}