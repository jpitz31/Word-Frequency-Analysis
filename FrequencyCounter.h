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

#ifndef FREQUENCYCOUNTER_H
#define FREQUENCYCOUNTER_H

#include <map>
#include <vector>


class frequencyCounter
{
private:
    std::string word_;
    char chr_;

public:
    typedef struct
    {
        std::string word;
        int count;
    } words;

    typedef struct
    {
        char chr;
        int count;
    } characters;

    bool operator()(const frequencyCounter::words &item) const;
    bool operator()(const frequencyCounter::characters &item) const;

    bool operator() (const std::string &item) const;
    bool operator() (const int &item) const;

    bool isWord (const std::string &word);
    bool isChar (const char &chr);

    std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems);
    std::vector<std::string> split(const std::string &s, char delim);

    template<typename A, typename B>
    std::pair<B,A> flip_pair(const std::pair<A,B> &p);
    template<typename A, typename B>
    std::map<B,A> flip_map(const std::map<A,B> &src);

    void parseText(const std::vector<std::string> &results, std::vector<frequencyCounter::words> &words,
        std::vector<frequencyCounter::characters> &characters);

    void parseTextMap(const std::vector<std::string> &results, std::map<std::string, int> &words,
        std::map<char, int> &characters);

};

template <typename T, typename B>
class compare
{
private:
    B key_;

public:
  compare(const B &key);
  bool operator()(const T &item) const;

};

class wordCmp
{
private:
    std::string word_;

public:
  wordCmp(const std::string &word);
  bool operator()(const frequencyCounter::words &item) const;

};

class chrCmp
{
private:
    char chr_;

public:
  chrCmp(const char &chr);
  bool operator()(const frequencyCounter::characters &item) const;

};

class wordCmpMap
{
private:
    std::string word_;

public:
  wordCmpMap(const std::string &word);
  bool operator()(const std::string &item) const;

};

class chrCmpMap
{
private:
    char chr_;

public:
  chrCmpMap(const char &chr);
  bool operator()(const int &item) const;

};

template <typename T>
struct  compareByCount
{
    bool operator()(const T &item1,
        const T &item2)
    {
        return (item1.count > item2.count);
    }
};

struct  compareByChrCount
{
    bool operator()(const frequencyCounter::characters &chr1,
        const frequencyCounter::characters &chr2)
    {
        return (chr1.count > chr2.count);
    }
};

struct compareByWordCount
{
    bool operator()(const frequencyCounter::words &word1,
    const frequencyCounter::words &word2)
    {
        return (word1.count > word2.count);
    }
};

template<typename A, typename B>
std::pair<B,A> frequencyCounter::flip_pair(const std::pair<A,B> &p)
{
    return std::pair<B,A>(p.second, p.first);
}

template<typename A, typename B>
std::map<B,A> frequencyCounter::flip_map(const std::map<A,B> &src)
{
    std::map<B,A> dst;
    std::transform(src.begin(), src.end(), std::inserter(dst, dst.begin()),
                   flip_pair<A,B>);
    return dst;
}



#endif // FREQUENCYCOUNTER_H
