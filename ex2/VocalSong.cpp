#include "VocalSong.h"

VocalSong::VocalSong(const std::string& title, const std::string& tags,
					 const std::string& lyrics, const std::string& author) :
	Song(title, tags, lyrics, author)
{
}

VocalSong::~VocalSong()
{
}

inline int VocalSong::containsWord(const std::string& word) const
{
	return _data.count(word);
}

std::string VocalSong::getDetails() const
{
	return "lyrics by: " + _author;
}