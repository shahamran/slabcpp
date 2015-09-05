#include "VocalSong.h"

/**
 * Constructor for a VocalSong object.
 * @param title The song's title
 * @param tagsStr A list of tags and their weight separated by spaces - <tag> <weight> ...
 * @param data The data for this song separated by spaces.
 * @param author The author of this song (lyrics , performer)
 */
VocalSong::VocalSong(const std::string& title, const std::string& tags,
					 const std::string& lyrics, const std::string& author) :
	Song(title, tags, lyrics, author)
{
}

/**
 * No special destructor implementation.
 */
VocalSong::~VocalSong()
{
}

/**
 * Checks if a given word appears in this song's lyrics.
 * @param word A word to check.
 * @return The number of times this words appears in the lyrics.
 */
int VocalSong::containsWord(const std::string& word) const
{
	return _data.count(word);
}

/**
 * @return The string: "lyrics by: <lyricsBy>"
 */
inline std::string VocalSong::getDetails() const
{
	return "lyrics by: " + _author;
}