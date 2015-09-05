#ifndef _VOCAL_SONG_H
#define _VOCAL_SONG_H

#include "Song.h"

/**
 * This class represents a song that has lyrics in it.
 */
class VocalSong : public Song
{
public:
	/**
	 * Constructor for a VocalSong object.
	 * @param title The song's title
	 * @param tagsStr A list of tags and their weight separated by spaces - <tag> <weight> ...
	 * @param data The data for this song separated by spaces.
	 * @param author The author of this song (lyrics , performer)
	 */
	VocalSong(const std::string& title, const std::string& tags, 
			  const std::string& lyrics, const std::string& author);

	/**
	 * Virtual destructor.
	 */
	virtual ~VocalSong();

	/**
	 * Checks if a given word appears in this song's lyrics.
	 * @param word A word to check.
	 * @return The number of times this words appears in the lyrics.
	 */
	int containsWord(const std::string& word) const override;

	/**
	 * VocalSong has no instruments specified.
	 * @param instrument The instrument to check.
	 * @return Always false.
	 */
	bool hasInstrument(const std::string& instrument) const override
	{
		UNUSED(instrument);
		return false;
	}

	/**
	 * @return The string: "lyrics by: <lyricsBy>"
	 */
	std::string getDetails() const override;
};

#endif
