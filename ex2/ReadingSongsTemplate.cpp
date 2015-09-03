#include <string>
#include <cstdlib>
#include <cassert>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <list>
#include <vector>


const std::string SEPARATOR = "=";
const std::string END_OF_SONGS = "***";
const std::string TITLE = "title";
const std::string TAGS = "tags";
const std::string LYRICS = "lyrics";
const std::string LYRICS_BY = "lyricsBy";
const std::string INSTRUMENTS = "instruments";
const std::string PERFORMED_BY = "performedBy";
const std::string BPM = "bpm";
/**
 * return all the line between {}
 */
std::string getWordList(const std::string line)
{

    size_t pos1 = line.find("{");
    size_t pos2 = line.find("}");

    return line.substr(pos1+1,pos2-pos1-1);
}


/**
* This can either be a basis for a member function of some class or static function or whatever...
*/
xxxx xxxx::readSongsFromFile(std::string songsFileName)
{

    std::ifstream instream(songsFileName.c_str());
    if (!instream.is_open())
    {
        std::cerr << "Error! Can't open file: " << songsFileName << "." << std::endl;
    }

    std::string line = "";



    int lastSong = 0;

    while(instream.good() && !lastSong)
    {
        if (line.compare(SEPARATOR) != 0)
        {
            getline(instream, line);
            // Expect a line of "="
            if (END_OF_SONGS.compare(line) == 0)
            {
                lastSong = 1;
                break;
            }

        }

        getline(instream, line);
        // Expect a line of "title: ..."
        size_t pos = TITLE.size() + 2;
        std::string title = line.substr(pos);

        getline(instream, line);
        // Expect a line of "tags: {...}"
        std::string tags = getWordList(line);

        std::string lyrics = "";
        std::string lyricsBy = "";
        std::string instruments = "";
        std::string performedBy = "";
        std::string bpmStr = "";

        getline(instream, line);
        // Expect either lyrics or instruments.
        if (line.substr(0, LYRICS.size()).compare(LYRICS) == 0)
        {
            // Then we have a lyric song

            // Lets get the lyrics:
            lyrics = getWordList(line);

            // Lets get the lyricsBy:
            getline(instream, line);
            pos = LYRICS_BY.size() + 2;
            lyricsBy = line.substr(pos);

            // TODO....
        }
        else
        {
            // Then we have an instrumental song

            // Lets get the instruments:
            instruments = getWordList(line);

            // Lets get the performedBy:
            getline(instream, line);
            pos = PERFORMED_BY.size() + 2;
            performedBy = line.substr(pos);

            // Lets see if we have bpm:
            if (!instream.good())
            {
                break;
            }
            getline(instream, line);
            if (END_OF_SONGS.compare(line) == 0)
            {
                lastSong = 1;
            }


            if (line.substr(0, BPM.size()).compare(BPM) == 0)
            {

                pos = BPM.size() + 2;
                bpmStr = line.substr(pos);

                // TODO....
            }
            else
            {
                 assert ( (line.compare(SEPARATOR) == 0) || (line.compare(END_OF_SONGS) == 0));


                 // TODO....
            }
        }
    }

    instream.close();

    // return something
}

