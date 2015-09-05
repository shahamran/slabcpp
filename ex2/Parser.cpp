#include "Parser.h"
#include <sstream>
#include <fstream>

const char NAME_SUFFIX = ':',
		   BPM_SEP = ',',
		   OPEN_GROUP = '{',
		   CLOSE_GROUP = '}';

const std::string SEPARATOR = "=",
				  END_OF_SONGS = "***",
				  TITLE = "title",
				  TAGS = "tags",
				  LYRICS = "lyrics",
				  LYRICS_BY = "lyricsBy",
				  INSTRUMENTS = "instruments",
				  PERFORMED_BY = "performedBy",
				  BPM = "bpm";

inline std::string& Parser::parseNamedLine(std::string& dest, const std::string& line)
{
	dest = line.substr(line.find(NAME_SUFFIX) + 2);
	return dest;
}

std::string& Parser::parseListLine(std::string& dest, const std::string& line) 
{
	size_t pos1 = line.find(OPEN_GROUP), pos2 = line.find(CLOSE_GROUP);
	dest = line.substr(pos1 + 1, pos2 - pos1 - 1);
	return dest;
}

Parser::Parameters& Parser::parseParameters(Parameters& prms, const std::string& fileName)
{
	std::ifstream instream(fileName.c_str());
	if (!instream.is_open())
	{
		std::cerr << "Error! Can't open file: " << fileName << "." << std::endl;
	}
	// Empty destination parameters list.
	prms.clear();
	std::string line = "",
			    dest = ""; // A 'temporary' string for small strings in the line.

	// Tags line
	std::getline(instream, line);
	std::istringstream(parseNamedLine(dest, line)) >> prms._tagMatchScore;

	// Lyrics line
	std::getline(instream, line);
	std::istringstream(parseNamedLine(dest, line)) >> prms._lyricsMatchScore;

	// Instruments line
	std::getline(instream, line);
	std::istringstream(parseNamedLine(dest, line)) >> prms._instrumentMatchScore;

	// BpmLikelihood line
	std::getline(instream, line);
	std::istringstream(parseNamedLine(dest, line)) >> prms._bpmLikelihoodWeight;

	// Insert Bpm special words into the bpm words map in the parameters struct
	BpmWord bpmWord; // BpmWord is a std::pair in which the first item is the word
					 // and the second item is a std::pair of 2 doubles: m, s.
	size_t colons, comma;
	while (instream.good())
	{
		std::getline(instream, line);
		colons = line.find(NAME_SUFFIX);
		comma = line.find(BPM_SEP);
		bpmWord.first = line.substr(0, colons); // The bpm special word
		std::istringstream(line.substr(colons + 1, comma)) >> bpmWord.second.first; // m
		std::istringstream(line.substr(comma + 1)) >> bpmWord.second.second;        // s
		prms._bpmWords.insert(bpmWord);
	}
	instream.close();
	return prms;
}

Parser::StringVector& Parser::parseQueries(StringVector& queries, const std::string fileName)
{
	std::ifstream instream(fileName.c_str());
	if (!instream.is_open())
	{
		std::cerr << "Error! Can't open file: " << fileName << "." << std::endl;
	}
	// Empty destination queries list.
	queries.clear();
	std::string line = "";
	while (instream.good())
	{
		std::getline(instream, line);
		if (line.size() > 0)
			queries.push_back(line);
	}
	instream.close();
	return queries;
}

Parser::SongsList& Parser::parseSongs(SongsList& songs, const std::string& fileName)
{
	std::ifstream instream(fileName.c_str());
	if (!instream.is_open())
	{
		std::cerr << "Error! Can't open file: " << fileName << "." << std::endl;
	}
	// Empty destination songs list.
	songs.clear();
	std::string line = "",
				title = "",
				tags = "",
				data = "",
				author = "",
				bpmStr = "";
	bool lastSong = false, firstSong = true, isVocal = false;
	double bpm = 0.0;
	Song* song;
	getline(instream, line);
	while (instream.good() && !lastSong)
	{
		// Check if *** is reached.
		if (line.compare(END_OF_SONGS) == 0)
		{
			lastSong = true;
		}
		// If *** or = were reached, create a new song
		if (lastSong || line.compare(SEPARATOR) == 0)
		{
			if (!firstSong) // Checks that we didn't reach the first =
			{
				if (isVocal)
				{
					song = new VocalSong(title, tags, data, author);
					
				}
				else
				{
					song = new InstrumentalSong(title, tags, data, author, bpm);
					bpm = 0.0;
				}
				// Add the new song to the songs list with no rating.
				songs.push_back(song);
			}
			else
			{
				firstSong = false;
			}
			if (lastSong)
				break;
		}
		// Get title
		getline(instream, line);
		parseNamedLine(title, line);
		// Get tags
		getline(instream, line);
		parseListLine(tags, line);
		// Get data (lyrics / instruments)
		getline(instream, line);
		parseListLine(data, line);
		// Determine whether this is a vocal or instrumental song
		isVocal = line.find(LYRICS) == 0 ? true : false;
		// Get author (performer / composer)
		getline(instream, line);
		parseNamedLine(author, line);
		// If this is an instrumental song, check if there is a bpm value.
		if (!isVocal)
		{
			getline(instream, line);
			if (line.find(BPM) == 0)
			{
				parseNamedLine(bpmStr, line);
				std::istringstream(bpmStr) >> bpm;
				getline(instream, line);
			}
		}
		else
		{
			getline(instream, line);
		}
	}
	instream.close();
	return songs;
}