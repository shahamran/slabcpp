#ifndef _INSTRUMENTAL_SONG_H
#define _INSTRUMENTAL_SONG_H

#include "Song.h"

/**
 * A class that represents an instrumental song. Inherits from Song.
 */
class InstrumentalSong : public Song
{
public:
	/**
	 * Cosntructs a new InstrumentalSong object.
	 * @param title The song's title
	 * @param tagsStr A list of tags and their weight separated by spaces - <tag> <weight> ...
	 * @param data The data for this song separated by spaces.
	 * @param author The author of this song (lyrics , performer)
	 * @param bpm The bpm value of this song ( default is NO_BPM (0.0) )
	 */
	InstrumentalSong(const std::string& title, const std::string& tags,
					 const std::string& instruments, const std::string& performer,
					 double bpm = NO_BPM);
	
	/**
	 * A virtual destructor.
	 */
	virtual ~InstrumentalSong();

	/**
	 * An instrumental song has, by definition, no lyrics.
	 * @param word The word to check
	 * @return Always 0.
	 */
	int containsWord(const std::string& word) const override
	{
		UNUSED(word);
		return 0;
	}
	
	/**
	 * Checks if a given instrument is in this song.
	 * @param instrument The instrument to check.
	 * @return true if the instrument is in this song, false otherwise.
	 */
	bool hasInstrument(const std::string& instrument) const override;

	/**
	 * @return the string: "performed by: <the performer>"
	 */
	std::string getDetails() const override;
};

#endif
