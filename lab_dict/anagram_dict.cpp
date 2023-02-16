/**
 * @file anagram_dict.cpp
 * Implementation of the AnagramDict class.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include "anagram_dict.h"
#include <algorithm>
#include <fstream>
#include <tgmath.h>

using std::string;
using std::vector;
using std::ifstream;

/**
 * Constructs an AnagramDict from a filename with newline-separated
 * words.
 * @param filename The name of the word list file.
 */
AnagramDict::AnagramDict(const string& filename)
{
    ifstream words(filename);
    string word;
    if (words.is_open()) {
        while (getline(words, word)) {
            add_word_to_dict(word);
        }
    }
}

/**
 * Constructs an AnagramDict from a vector of words.
 * @param words The vector of strings to be used as source words.
 */
AnagramDict::AnagramDict(const vector<string>& words)
{
    for (const string& word : words) {
        add_word_to_dict(word);
    }
}

/**
 * @param word The word to add to the dictionary
 * Adds the word as a (key, value) pair to the dictionary.
 * NOTE: word is the value. You will need to decide an appropriate key
 * for the word.
 */
void AnagramDict::add_word_to_dict(const std::string& word)
{
    double sum = 0.0;
    for (int i=0; i < (int)word.size(); i++) {
        sum = sum + pow((int)word[i], 2.7);
    }
    string temp = std::to_string(sum);
    auto lookup = dict.find(temp);
    if (lookup == dict.end()) {
        dict.insert({temp, {word}});
    }
    else {
        auto lookup2 = lookup->second.begin();
        for (; lookup2 != lookup->second.end(); lookup2++) {
            word.compare(*lookup2);
        }
        if (lookup2 == lookup->second.end()) {
            lookup->second.push_back(word);
        }
    }
}

/**
 * @param word The word to find anagrams of.
 * @return A vector of strings of anagrams of the given word. Empty
 * vector returned if no anagrams are found or the word is not in the
 * word list.
 */
vector<string> AnagramDict::get_anagrams(const string& word) const
{
    double sum = 0.0;
    vector<string> ret;
    for (int i=0; i < (int)word.size(); i++) {
        sum = sum + pow((int)word[i], 2.7);
    }
    string temp = std::to_string(sum);
    auto lookup = dict.find(temp);
    if (lookup == dict.end()) {
        return ret;
    }
    else {
        return lookup->second;
    }
}

/**
 * @return A vector of vectors of strings. Each inner vector contains
 * the "anagram siblings", i.e. words that are anagrams of one another.
 * NOTE: It is impossible to have one of these vectors have less than
 * two elements, i.e. words with no anagrams are ommitted.
 */
vector<vector<string>> AnagramDict::get_all_anagrams() const
{
    /* Your code goes here! */
    vector<vector<string>> ret;
    for (auto lookup = dict.begin(); lookup != dict.end(); lookup++) {
        if (lookup->second.size()>1)
        ret.push_back(lookup->second);
    }
    // Stub value - remove when you are done
    return ret;
}
