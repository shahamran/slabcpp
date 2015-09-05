#include "Parser.h"
#include <sstream>

// Some char constants
const char NAME_SUFFIX = ':',
		   BPM_SEP = ',',
		   OPEN_GROUP = '{',
		   CLOSE_GROUP = '}';

// Some string constants (important for string methods)
const std::string SEPARATOR = "=",
				  END_OF_SONGS = "***",
				  TITLE = "title",
				  TAGS = "tags",
				  LYRICS = "lyrics",
				  LYRICS_BY = "lyricsBy",
				  INSTRUMENTS = "instruments",
				  PERFORMED_BY = "performedBy",
				  BPM = "bpm";

/**
 * Parses a line that starts with a name.
 * i.e for a line of the following format: <name>: <data>
 * this function returns <data>.
 */
inline std::string& Parser::parseNamedLine(std::string& dest, const std::string& line)
{
	dest = line.substr(line.find(NAME_SUFFIX) + 2); // + 1 for <:> +1 for <space>
	return dest;
}

/**
 * Parses a line that contains a list (bounded by { and } chars).
 */
std::string& Parser::parseListLine(std::string& dest, const std::string& line) 
{
	size_t pos1 = line.find(OPEN_GROUP), pos2 = line.find(CLOSE_GROUP);
	dest = line.substr(pos1 + 1, pos2 - pos1 - 1);
	return dest;
}

/**
 * Parses a parameters file to initialize a given parameters object.
 * @param prms The parameters object to initialize.
 * @param fileName The parameters file name.
 * @return A reference to prms.
 */
Parser::Parameters& Parser::parseParameters(Parameters& prms, const std::string& fileName)
{
	// Check that the file exists (same for all parsing methods)
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
		if (colons == std::string::npos || colons == 0) // Make sure this is a line with ':'
			continue;									// and that this is not an empty word
		comma = line.find(BPM_SEP);
		bpmWord.first = line.substr(0, colons); // The bpm special word
		std::istringstream(line.substr(colons + 1, comma)) >> bpmWord.second.first; // m
		std::istringstream(line.substr(comma + 1)) >> bpmWord.second.second;        // s
		prms._bpmWords.insert(bpmWord);
	}
	instream.close();
	return prms;
}

/**
 * Parses a songs file to initialize a given songs list (vector).
 * Important note: this method ALLOCATES memory on the heap.
 * Use 'delete' on all (Song*) in SongsList.
 * @param songs A vector of (Song*)
 * @param fileName The songs file name
 * @return a reference to the songs parameter
*/
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
	Song* song; // Created song.
	getline(instream, line);
	while (instream.good() && !lastSong)
	{
		// Check if '***' was reached.
		if (line.compare(END_OF_SONGS) == 0)
		{
			lastSong = true;
		}
		// If '***' or '=' were reached, create a new song
		if (lastSong || line.compare(SEPARATOR) == 0)
		{
			if (!firstSong) // Checks that we didn't reach the first '='
			{
				if (isVocal) // Decide what kind of song to create.
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
			if (line.find(BPM) == 0) // Checks if this is a bpm line
			{
				parseNamedLine(bpmStr, line);
				std::istringstream(bpmStr) >> bpm;
				getline(instream, line); // Move to the next line.
			}
		}
		else
		{
			getline(instream, line); // Move to the next line.
		}
	}
	instream.close();
	return songs;
}