#include "InstrumentalSong.h"

/**
 * Cosntructs a new InstrumentalSong object.
 * @param title The song's title
 * @param tagsStr A list of tags and their weight separated by spaces - <tag> <weight> ...
 * @param data The data for this song separated by spaces.
 * @param author The author of this song (lyrics , performer)
 * @param bpm The bpm value of this song ( default is NO_BPM (0.0) )
 */
InstrumentalSong::InstrumentalSong(const std::string& title, const std::string& tags,
								   const std::string& instruments, const std::string& performer,
								   double bpm) :
	Song(title, tags, instruments, performer, bpm)
{
}

/**
 * No special implementation for destructor
 */
InstrumentalSong::~InstrumentalSong()
{
}

/**
 * Checks if a given instrument is in this song.
 * @param instrument The instrument to check.
 * @return true if the instrument is in this song, false otherwise.
 */
bool InstrumentalSong::hasInstrument(const std::string& instrument) const
{
	return (_data.find(instrument) != _data.end());
}

/**
 * @return the string: "performed by: <the performer>"
 */
inline std::string InstrumentalSong::getDetails() const
{
	return "performed by: " + _author;
}