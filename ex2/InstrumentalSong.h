#ifndef _INSTRUMENTAL_SONG_H
#define _INSTRUMENTAL_SONG_H
#include "Song.h"
#include <unordered_set>

class InstrumentalSong : public Song
{
public:
	InstrumentalSong(const std::string& title, const std::string& tags,
					 const std::string& instruments, const std::string& performer,
					 double bpm = NO_BPM);
	virtual ~InstrumentalSong();

	int containsWord(const std::string& word) const override
	{
		UNUSED(word);
		return 0;
	}

	bool hasInstrument(const std::string& instrument) const override;
	std::string getDetails() const override;
};

#endif
