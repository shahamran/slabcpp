#ifndef _VOCAL_SONG_H
#define _VOCAL_SONG_H
#include "Song.h"

class VocalSong : public Song
{
public:
	VocalSong(const std::string& title, const std::string& tags, 
			  const std::string& lyrics, const std::string& author);
	virtual ~VocalSong();
	int containsWord(const std::string& word) const;
	std::string getDetails() const override;
};

#endif
