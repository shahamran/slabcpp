#include <iostream>
#include <string>
#include <unordered_map>
#include <cmath>
#include "Song.h"
#include "Parser.h"

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1
#define SEPARATOR "----------------------------------------"
#define TAB '\t'
#define MINIMAL_SCORE 0

/**
 * An enum for the order of arguments from the command line
 */
enum Argument
{
	PROG_NAME = 0,
	DATA_FILE = 1,
	PARAMS_FILE = 2,
	QUERIES_FILE = 3,
	NUM_OF_ARGS // Gets the number 3 + 1 = 4 which is the number of args
				// (for possible future change of the number of arguments)
};

/**
 * Update each song's score according to the given query.
 * Save the results to a SortedSongsList (multimap<int, song*> sorted by descending
 * order of keys).
 * @param output The output SortedSongsList object.
 * @param songs The list of songs
 * @param params The parameters object
 * @param query The query word
 */
void updateSongsRating(Parser::SortedSongsList& output, const Parser::SongsList& songs, 
					   const Parser::Parameters& params, const std::string& query)
{
	output.clear(); // Clean up the old list of songs.
	int rating = 0;
	Parser::BpmWordsMap::const_iterator foundBpmWord;
	double m, s, bpm, bpmLikelihood;
	Song* song = nullptr;
	for (Parser::SongsList::const_iterator curr = songs.begin(); curr != songs.end(); curr++)
	{
		song = *curr;
		rating = 0;
		rating += (song->hasTag(query)) * params._tagMatchScore;
		rating += (song->containsWord(query)) * params._lyricsMatchScore;
		rating += (song->hasInstrument(query)) * params._instrumentMatchScore;
		foundBpmWord = params._bpmWords.find(query);
		// If the query is a know bpm word, calculate the bpm score
		if (foundBpmWord != params._bpmWords.end())
		{
			bpm = song->getBpm();
			if (bpm != NO_BPM) // If the song has bpm info.
			{
				m = foundBpmWord->second.first;
				s = foundBpmWord->second.second;
				bpmLikelihood = exp(-std::pow(bpm - m, 2) / (2 * std::pow(s, 2)));
				rating += (int)floor(bpmLikelihood * params._bpmLikelihoodWeight);
			}
		}
		output.insert(std::make_pair(rating, song));
	}
}

/**
 * Prints the given song's details and its score.
 * @param result A pair<int, Song*> where the first argument is the score
 * and the second is the pointer to the song.
 */
void printSong(const std::pair<int, Song*>& result)
{
	const int rating = result.first;
	const Song* song = result.second;
	std::cout << song->getTitle() << TAB << rating << TAB << song->getDetails() << std::endl;
}

/**
 * The main function.
 * Gets the data from the given file names (assumes files are in valid format), 
 * runs the calculations and prints the results. 
 * Only songs with score > MINIMAL_SCORE (0) are printed.
 */
int main(int argc, char* argv[])
{
	// Check if the program was called with a correct number of arguments
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
	Parser::SongsList songsList;
	Parser::SortedSongsList sortedList;
	Parser::StringVector queries;
	// Get relevant data from files:
	Parser::parseParameters(prms, paramsFileName);
	Parser::parseSongs(songsList, dataFileName);
	Parser::parseQueries(queries, queriesFileName);
	// For each query, update the songs scores and print the results
	for (Parser::StringVector::iterator curr = queries.begin(); curr != queries.end(); curr++)
	{
		updateSongsRating(sortedList, songsList, prms, *curr);
		std::cout << SEPARATOR << std::endl << "Query word: " << *curr << std::endl << std::endl;
		for (Parser::SortedSongsList::iterator i_song = sortedList.begin();
			 i_song != sortedList.end(); i_song++)
		{
			if (i_song->first > MINIMAL_SCORE) // Check if the score of this song is > 0
				printSong(*i_song);
			else // sortedList is sorted, so all the next songs have scores < 0
				break;
		}
	}
	// Clean up (data was allocated on the heap by Parser::parseSongs method)
	for (Parser::SongsList::iterator curr = songsList.begin(); curr != songsList.end(); curr++)
	{
		delete (*curr);
	}
	return EXIT_SUCCESS;
}