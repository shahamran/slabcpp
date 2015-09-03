#include <iostream>
#include <string>
#include <unordered_map>

#define NUM_OF_ARGS 4
#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

typedef std::unordered_map<std::string, std::pair<double, double>> BpmWordsMap;

struct Parameters
{
	int tagMatchScore;
	int lyricsMatchScore;
	int instrumentMatchScore;
	int bpmLikelihoodWeight;
	BpmWordsMap bpmWords;
};

enum Argument
{
	PROG_NAME = 0,
	DATA_FILE = 1,
	PARAMS_FILE = 2,
	QUERIES_FILE = 3
};

std::string getWordList(const std::string line)
{

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

	return EXIT_SUCCESS;
}