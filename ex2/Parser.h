#ifndef _PARSER_H
#define _PARSER_H

#include <iostream>
#include <unordered_map>
#include <map> // for multimap
#include <vector>
#include <fstream> // for files handling
#include <functional> // For the greater<int> functor
#include "VocalSong.h"
#include "InstrumentalSong.h"

/**
 * This class is a collection of static methods to parse files for the program.
 */
class Parser
{
public:
	/**
	 * SongsList: A vector of song pointers.
	 * SortedSongsList: A multimap<int, Song*> of songs and their ratings.
	 * BpmWord: A pair that contains the bpm word, 'm' and 's' values.
	 * BpmWordsMap: A map of the bpm words for fast retrieval.
	 */
	typedef std::vector<Song*> SongsList;
	typedef std::multimap<int, Song*, std::greater<int>> SortedSongsList;
	typedef std::pair<std::string, std::pair<double, double>> BpmWord;
	typedef std::unordered_map<std::string, std::pair<double, double>> BpmWordsMap;

	/**
	 * A struct that contains all the relevant parameters for songs rating.
	 */
	struct Parameters
	{
		void clear()
		{
			_tagMatchScore = 0;
			_lyricsMatchScore = 0;
			_instrumentMatchScore = 0;
			_bpmLikelihoodWeight = 0;
			_bpmWords.clear();
		}
		int _tagMatchScore;
		int _lyricsMatchScore;
		int _instrumentMatchScore;
		int _bpmLikelihoodWeight;
		BpmWordsMap _bpmWords;
	};

	/**
	 * Parses a parameters file to initialize a given parameters object.
	 * @param prms The parameters object to initialize.
	 * @param fileName The parameters file name.
	 * @return A reference to prms.
	 */
	static Parameters& parseParameters(Parameters& prms, const std::string& fileName);

	/**
	 * Parses a songs file to initialize a given songs list (vector).
	 * Important note: this method ALLOCATES memory on the heap. 
	 * Use 'delete' on all (Song*) in SongsList.
	 * @param songs A vector of (Song*)
	 * @param fileName The songs file name
	 * @return a reference to the songs parameter
	 */
	static SongsList& parseSongs(SongsList& songs, const std::string& fileName);

private:
	/**
	 * A private constructor to prevent creation of Parser objects.
	 */
	Parser();

	/**
	 * A private operator= to prevent copying of Parser objects.
	 */
	Parser& operator=(const Parser& other);

	/**
	 * Parses a line that contains a list (bounded by { and } chars).
	 */
	static std::string& _parseListLine(std::string& dest, const std::string& line);

	/**
	 * Parses a line that starts with a name.
	 * i.e for a line of the following format: <name>: <data>
	 * this function returns <data>.
	 */
	static std::string& _parseNamedLine(std::string& dest, const std::string& line);
};

#endif