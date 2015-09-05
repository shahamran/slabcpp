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
 * Gets a sorted list of songs and a query string and prints them in the required format.
 * @param sortedList The sorted songs list
 * @param query The query string
 */
void printSortedList(const Parser::SortedSongsList& sortedList, const std::string& query)
{
	std::cout << SEPARATOR << std::endl << "Query word: " << query << std::endl << std::endl;
	Song* song;
	int score;
	for (Parser::SortedSongsList::const_iterator i_song = sortedList.begin();
	i_song != sortedList.end(); i_song++)
	{
		if (i_song->first > MINIMAL_SCORE) // Check if the score of this song is > 0
		{ // Prints the song.
			score = i_song->first;
			song = i_song->second;
			std::cout << song->getTitle() << TAB << score << TAB << song->getDetails() 
					  << std::endl;
		}			
		else // sortedList is sorted, so all the next songs have scores < 0
		{
			break;
		}
	}
}

void runQueries(const std::string& queriesFile, const Parser::Parameters& params,
				const Parser::SongsList& songs)
{
	// Check input file
	std::ifstream instream(queriesFile.c_str());
	if (!instream.is_open())
	{
		std::cerr << "Error! Can't open file: " << queriesFile << "." << std::endl;
	}
	Parser::SortedSongsList sortedList; // The sorted list of songs.
	std::string query = "";
	while (instream.good())
	{
		std::getline(instream, query);
		if (query.size() == 0) // Ignore empty queries.
			continue;
		updateSongsRating(sortedList, songs, params, query);
		printSortedList(sortedList, query);
	}
	instream.close();
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
		std::cerr << "Usage: " << argv[PROG_NAME] << " <songs_data_file> "
				  << "<learned_parameters_file> <queries_file>" << std::endl;
		return EXIT_FAILURE;
	}

	std::string dataFileName(argv[DATA_FILE]),
				paramsFileName(argv[PARAMS_FILE]),
				queriesFileName(argv[QUERIES_FILE]);

	Parser::Parameters prms;
	Parser::SongsList songsList;
	Parser::SortedSongsList sortedList;
	// Get relevant data from files:
	Parser::parseParameters(prms, paramsFileName);
	Parser::parseSongs(songsList, dataFileName);
	// For each query, update the songs scores and print the results
	runQueries(queriesFileName, prms, songsList);
	// Clean up (data was allocated on the heap by Parser::parseSongs method)
	for (Parser::SongsList::iterator curr = songsList.begin(); curr != songsList.end(); curr++)
	{
		delete (*curr);
	}
	return EXIT_SUCCESS;
}