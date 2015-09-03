#ifndef _INSTRUMENTAL_SONG_H
#define _INSTRUMENTAL_SONG_H
#include "Song.h"
#include <unordered_set>

class InstrumentalSong : public Song
{
public:
	InstrumentalSong(std::string title, std::string tags, std::string instruments,
					 std::string performer, double bpm = NO_BPM);
	virtual ~InstrumentalSong();
	bool hasInstrument(std::string instrument) const;
	std::string getDetails() const override;
};

#endif
