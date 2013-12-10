// Program FrequencyCounter
// Author Joe Pitz
// Description parses a file and determines the count of words and characters
// used for cryptology analysis
//
// Copyright:  Creative Commmons CC BY SA NC
//
// Change summary
//
// Created 12/01/2013
//

#include <cstdlib>
#include <algorithm>
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <iterator>

#include "FrequencyCounter.h"


std::vector<std::string>& frequencyCounter::split(const std::string &s, char delim, std::vector<std::string> &elems)
{
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

std::vector<std::string> frequencyCounter::split(const std::string &s, char delim)
{
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}

wordCmp::wordCmp(const std::string &word) : word_(word){}
chrCmp::chrCmp(const char &chr) : chr_(chr){}

bool wordCmp::operator()(const frequencyCounter::words &item) const
{
    return (item.word == wordCmp::word_);
}

bool chrCmp::operator()(const frequencyCounter::characters &item) const
{
    return (item.chr == chrCmp::chr_);
}


void frequencyCounter::parseText(const std::vector<std::string> &results, std::vector<frequencyCounter::words> &wordsVect,
    std::vector<frequencyCounter::characters> &charVect)
{
    try
    {
        for(auto& word: results)
        {
            std::vector<frequencyCounter::words>::iterator itwd = std::find_if(std::begin(wordsVect),
                std::end(wordsVect), wordCmp::wordCmp(word));

            if (itwd == wordsVect.end() )
            {
                frequencyCounter::words newWord;
                newWord.word = word;
                newWord.count = 0;
                newWord.count += 1;
                wordsVect.push_back(newWord);
            }
            else
            {
                (*itwd).count++;
            }

            for(char chr : word)
            {
                std::vector<frequencyCounter::characters>::iterator itch = std::find_if(std::begin(charVect),
                    std::end(charVect), chrCmp::chrCmp(chr));

                if (itch == charVect.end() )
                {
                    frequencyCounter::characters newChar;
                    newChar.chr = chr;
                    newChar.count = 0;
                    newChar.count += 1;
                    charVect.push_back(newChar);
                }
                else
                {
                   (*itch).count++;
                }
            }
        }
    }
    catch (...)
    {
      std::cout << "Exception occurred while parsing message file\n";
    }

    return;
}

void frequencyCounter::parseTextMap(const std::vector<std::string> &results, std::map<std::string, int> &wordsMap,
    std::map<char, int> &charMap)
{
    try
    {
        for(auto& word: results)
        {
             std::map<std::string, int>::iterator itwd = wordsMap.find(word);
            //std::map<std::string, int>::iterator itwd = std::find_if(std::begin(wordsMap),
            //     std::end(wordsMap), wordCmpMap(word));

            if (itwd == wordsMap.end() )
            {
                wordsMap[word] = 1;
            }
            else
            {
                itwd->second++;
            }

            for(char chr : word)
            {
                std::map<char, int>::iterator itch = charMap.find(chr);
                // std::map<char, int>::iterator itch = std::find_if(std::begin(charMap),
                //    std::end(charMap),  chrCmpMap(chr));

                if (itch == charMap.end() )
                {
                    charMap[chr] = 1;
                }
                else
                {
                   itch->second++;
                }
            }
        }
    }
    catch (...)
    {
      std::cout << "Exception occurred while parsing message file\n";
    }

    return;
}


