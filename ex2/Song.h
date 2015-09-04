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
	Song(const std::string& title, const std::string& tagsStr, const std::string& data,
		 const std::string& author, double bpm = NO_BPM);

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

	virtual int containsWord(const std::string& word) const = 0;

	virtual bool hasInstrument(const std::string& instrument) const = 0;

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
	int hasTag(const std::string& tag) const;

	inline double getBpm() const
	{
		return _bpm;
	}

	/**
	 */
	static Song * createSong(std::string title,std::string tags, std::string data,
							  std::string author, double bpm = NO_BPM);
protected:
	typedef std::unordered_map<std::string, int> TagsList;
	typedef std::unordered_multiset<std::string> DataList;
	std::string _title;
	TagsList _tags;
	DataList _data;
	std::string _author;
	double _bpm;
};

#endif