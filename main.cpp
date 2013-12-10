// Program FrequencyCounter
// Author Joe Pitz
// Description parses a file and determines the count of words and characters
// used for cryptology analysis
//
// Copyright:  Creative Commmons CC BY SA NC
//
// Command line arguments FrequencyCounter.exe <filename> <logfile
// filename is text file containing message to parse
// logfile is the text file that contains the work and character counts
//
// Change summary
//
// Created 12/01/2013
//

#include <QTime>
#include <cstdlib>
#include <cstdio>
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "FrequencyCounter.h"

int main(int argc, char *argv[])
{
    // declare variables
    std::vector<std::string> words;
    std::vector<frequencyCounter::words> wordCount;
    std::vector<frequencyCounter::characters> characterCount;

    std::string line;
    std::ofstream logfile;

    // Benchmark time
    QTime timer;
    timer.start();

    // check command line arguments
    if ( argc != 3 )
    {
        std::cout << "usage: " << argv[0] << " <filename> <logfile>\n";
        return 0;
    }

    // open file and check if open
    std::ifstream infile(argv[1]);

    if ( !infile.is_open())
    {
         std::cout << "Could not open " << argv[1] << " file\n";
         return 0;
    }

    frequencyCounter fc;

    // loop file, line by line
    while (std::getline(infile, line))
    {
        // split words from line
        words = fc.split(line, ' ');

        // parse characters and words
        fc.parseText(words, wordCount, characterCount);

        words.clear();

    }

    // sort the word and character vectors
    std::sort(wordCount.begin(), wordCount.end(), compareByWordCount());
    std::sort(characterCount.begin(), characterCount.end(), compareByChrCount());

    // write results to log file
    std::cout << "writing results to " << argv[1] << " file\n";

    logfile.open(argv[2]);
    logfile << "\nWords sorted by frequency\n\n";

    for(auto& word : wordCount)
        logfile << word.word << " = " << word.count << '\n';

    logfile << "\nCharacters sorted by frequency\n\n";

    for(auto& chrs : characterCount)
        logfile << chrs.chr << " = " << chrs.count << '\n';


    logfile.close();

    std::cout << "Done\n";

    std::cout << std::fixed;
    std::cout << std::setprecision(3);

    std::cout << "\nElapsed Time = " << timer.elapsed() * 0.001  << "\n";

    return 0;
}
