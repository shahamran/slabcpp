#ifndef _SONG_H
#define _SONG_H
#define NO_BPM 0.0

#include <iostream>
#include <unordered_map>
#include <unordered_set>

class Song
{
public:

	/**
	 * Constructor for a song object (abstract).
	 * @param title The song's title
	 * @param tagsStr A list of tags and their weight separated by spaces - <tag> <weight> ...
	 */
	Song(std::string title, std::string tagsStr, std::string data, \
		 std::string author, double bpm = 0.0);

	/**
	 * Virtual destructor for a song object;
	 */
	virtual ~Song();

	/**
	 * @return This song's title.
	 */
	inline std::string getTitle() const
	{
		return _title;
	};

	/**
	 * Pure virtual method for retrieving the song's details.
	 */
	virtual std::string getDetails() const = 0;

	/**
	 * Checks if this song has a given tag. If so, returns its value (weight). 
	 * Otherwise, returns 0.
	 * @param tag The string of a tag to check.
	 * @return The weight of the given tag if this songs contains it, 0 otherwise.
	 */
	int hasTag(std::string tag) const;

	inline virtual double getBpm() const
	{
		return _bpm;
	}

	/**
	 */
	static Song * createSong(std::string title,std::string tags, std::string data,
							  std::string author, double bpm = NO_BPM);
protected:
	std::string _title;
	std::unordered_map<std::string, int> _tags;
	std::unordered_multiset<std::string> _data;
	std::string _author;
	double _bpm;
};

#endif