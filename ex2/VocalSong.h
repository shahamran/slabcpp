#ifndef _VOCAL_SONG_H
#define _VOCAL_SONG_H
#include "Song.h"

class VocalSong : public Song
{
public:
	VocalSong(std::string title, std::string tags, std::string lyrics, std::string author);
	virtual ~VocalSong();
	int containsWord(std::string word) const;
	std::string getDetails() const override;
};

#endif
