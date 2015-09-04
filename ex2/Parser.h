#ifndef _PARSER_H
#define _PARSER_H

#include <unordered_map>
#include "VocalSong.h"
#include "InstrumentalSong.h"
#include <map>
#include <vector>
#include <functional>

class Parser
{
public:
	typedef std::multimap<int, Song*, std::greater<int>> SongsList;
	typedef std::pair<std::string, std::pair<double, double>> BpmWord;
	typedef std::unordered_map<std::string, std::pair<double, double>> BpmWordsMap;
	typedef std::vector<std::string> StringVector;

	struct Parameters
	{
		int _tagMatchScore;
		int _lyricsMatchScore;
		int _instrumentMatchScore;
		int _bpmLikelihoodWeight;
		BpmWordsMap _bpmWords;
	};

	Parameters& parseParameters(Parameters& prms, const std::string& fileName);

	SongsList& parseSongs(SongsList& songs, const std::string& fileName);

	StringVector& parseQueries(StringVector& queries, const std::string fileName);

private:

	Parser();

	Parser& operator=(const Parser& other);

	static std::string& parseListLine(std::string& dest, const std::string& line);

	static std::string& parseNamedLine(std::string& dest, const std::string& line);
};

#endif