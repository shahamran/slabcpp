#include "InstrumentalSong.h"

InstrumentalSong::InstrumentalSong(const std::string& title, const std::string& tags,
								   const std::string& instruments, const std::string& performer,
								   double bpm = NO_BPM) :
	Song(title, tags, instruments, performer, bpm)
{
}

InstrumentalSong::~InstrumentalSong()
{
}

inline bool InstrumentalSong::hasInstrument(const std::string& instrument) const
{
	return _data.count(instrument);
}

std::string InstrumentalSong::getDetails() const
{
	return "performed by: " + _author;
}