#include <iostream>
#include <string>
#include <unordered_map>
#include <cmath>
#include "Song.h"
#include "Parser.h"

#define NUM_OF_ARGS 4
#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1
#define SEPARATOR "----------------------------------------"
#define TAB '\t'
#define MINIMAL_SCORE 0



enum Argument
{
	PROG_NAME = 0,
	DATA_FILE = 1,
	PARAMS_FILE = 2,
	QUERIES_FILE = 3
};

void updateSongsRating(Parser::SongsList& output, const Parser::SongsList& songs, 
					   const Parser::Parameters& params, const std::string& query)
{
	output.clear();
	int rating = 0;
	Parser::BpmWordsMap::const_iterator foundBpmWord;
	double m, s, bpm, bpmLikelihood;
	
	for (Parser::SongsList::const_iterator curr = songs.begin(); curr != songs.end(); curr++)
	{
		rating = 0;
		rating += (curr->second->hasTag(query)) * params._tagMatchScore;
		rating += (curr->second->containsWord(query)) * params._lyricsMatchScore;
		rating += (curr->second->hasInstrument(query)) * params._instrumentMatchScore;
		foundBpmWord = params._bpmWords.find(query);
		if (foundBpmWord != params._bpmWords.end())
		{
			bpm = curr->second->getBpm();
			if (bpm != NO_BPM)
			{
				m = foundBpmWord->second.first;
				s = foundBpmWord->second.second;
				bpmLikelihood = floor(exp(-std::pow(bpm - m, 2) / (2 * std::pow(s, 2)))); // -----------------
				rating += (int)bpmLikelihood * params._bpmLikelihoodWeight;
			}
		}
		output.insert(std::make_pair(rating, curr->second));
	}
}

void printSong(const std::pair<int, Song*>& result)
{
	const int rating = result.first;
	const Song* song = result.second;
	if (rating <= MINIMAL_SCORE)
		return;
	std::cout << song->getTitle() << TAB << rating << TAB << song->getDetails() << std::endl;
}

int main(int argc, char* argv[])
{
	if (argc != NUM_OF_ARGS)
	{
		std::cout << "Usage: " << argv[PROG_NAME] << " <songs_data_file> "
				  << "<learned_parameters_file> <queries_file>" << std::endl;
		return EXIT_FAILURE;
	}
	std::string dataFileName(argv[DATA_FILE]),
				paramsFileName(argv[PARAMS_FILE]),
				queriesFileName(argv[QUERIES_FILE]);

	Parser::Parameters prms;
	Parser::SongsList songsList, sortedList;
	Parser::StringVector queries;
	Parser::parseParameters(prms, paramsFileName);
	Parser::parseSongs(songsList, dataFileName);
	Parser::parseQueries(queries, queriesFileName);
	for (Parser::StringVector::iterator curr = queries.begin(); curr != queries.end(); curr++)
	{
		updateSongsRating(sortedList, songsList, prms, *curr);
		std::cout << SEPARATOR << std::endl << "Query word: " << *curr << std::endl << std::endl;
		for (Parser::SongsList::iterator i_song = sortedList.begin();
			 i_song != sortedList.end(); i_song++)
		{
			printSong(*i_song);
		}
	}
	return EXIT_SUCCESS;
}