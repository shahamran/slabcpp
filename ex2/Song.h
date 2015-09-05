#ifndef _SONG_H
#define _SONG_H

#include <unordered_map>
#include <unordered_set>

#define UNUSED(x) (void)(x)
#define NO_BPM 0.0

/**
 * This is an abstract class that represents a song.
 * Holds the title, author, tags, data (lyrics / instruments) and bpm values.
 */
class Song
{
public:

	/**
	 * Constructor for a song object (abstract).
	 * @param title The song's title
	 * @param tagsStr A list of tags and their weight separated by spaces - <tag> <weight> ...
	 * @param data The data for this song separated by spaces.
	 * @param author The author of this song (lyrics , performer)
	 * @param bpm The bpm value of this song ( default is NO_BPM (0.0) )
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

	/**
	 * Pure virtual method to count the amount of times a given word
	 * is in this song's lyrics (if there are any).
	 */
	virtual int containsWord(const std::string& word) const = 0;

	/**
	 * Pure virtual method to determine whether a given instrument
	 * is in this song.
	 */
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

	/**
	 * @return the bpm value of this song if such exists,
	 * or NO_BPM (0.0) if not.
	 */
	inline double getBpm() const
	{
		return _bpm;
	}

protected:
	/**
	 * typedefs for the list of tags and data.
	 * Tags also have weight value, hence the map data structure.
	 * Data (like lyrics) can appear multiple times, hence the multiset DaSt.
	 */
	typedef std::unordered_map<std::string, int> TagsList;
	typedef std::unordered_multiset<std::string> DataList;

	std::string _title;
	TagsList _tags;
	DataList _data;
	std::string _author;
	double _bpm;
};

#endif