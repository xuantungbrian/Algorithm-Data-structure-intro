/**
 * @file common_words.cpp
 * Implementation of the CommonWords class.
 *
 * @author Zach Widder
 * @date Fall 2014
 */

#include "common_words.h"

#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <iterator>
#include <algorithm>

using std::string;
using std::vector;
using std::ifstream;
using std::cout;
using std::endl;
using std::feof;

string remove_punct(const string& str)
{
    string ret;
    std::remove_copy_if(str.begin(), str.end(), std::back_inserter(ret),
                        [](int c) { return std::ispunct(c); });
    return ret;
}

CommonWords::CommonWords(const vector<string>& filenames)
{
    // initialize all member variables
    init_file_word_maps(filenames);
    init_common();
}

void CommonWords::init_file_word_maps(const vector<string>& filenames)
{
    // make the length of file_word_maps the same as the length of filenames
    file_word_maps.resize(filenames.size());

    // go through all files
    for (size_t i = 0; i < filenames.size(); i++) {
        // get the corresponding vector of words that represents the current file
        vector<string> words = file_to_vector(filenames[i]);

        // go through all the words in the file
        /* Your code goes here! */
        for (int a=0; a<(int)words.size(); a++) {
            auto lookup = file_word_maps[i].find(words[a]);
            if (lookup != file_word_maps[i].end()) {
                lookup->second++;
            }
            else {
                file_word_maps[i].insert({words[a], 1});
            }
        }
    }
}

void CommonWords::init_common()
{
    /* Your code goes here!  */
    for (size_t i = 0; i < file_word_maps.size(); i++) {
        for (auto keys = file_word_maps[i].begin(); keys != file_word_maps[i].end(); keys++) {
            auto lookup = common.find(keys->first);
            if (lookup == common.end()) {
                common.insert({keys->first, keys->second});
            }
            else {
                lookup->second = lookup->second + keys->second;
            }
        }
    }
}

/**
 * @param n The number of times to word has to appear.
 * @return A vector of strings. The vector contains all words that appear
 * in each file >= n times.
 */
vector<string> CommonWords::get_common_words(unsigned int n) const
{
    /*for (auto keys = common.begin(); keys!=common.end(); keys++) {
        std::cout << keys->first << " " << keys->second << std::endl;
    }*/
    vector<string> out;
    int temp = 0;
    /* Your code goes here! */
    for (auto keys = common.begin(); keys!=common.end(); keys++) {
        if (keys->second >= file_word_maps.size()*n) {
            temp = 0;
            for (int i=0; i<(int)file_word_maps.size(); i++) {
                auto lookup = file_word_maps[i].find(keys->first);
                if (lookup != file_word_maps[i].end()) {
                    if (lookup->second >= n) {
                        temp++;
                    }
                }
            }
            if (temp == (int)file_word_maps.size()) {
                out.push_back(keys->first);
            }
        }
    }
    return out;
}

/**
 * Takes a filename and transforms it to a vector of all words in that file.
 * @param filename The name of the file that will fill the vector
 */
vector<string> CommonWords::file_to_vector(const string& filename) const
{
    ifstream words(filename);
    vector<string> out;

    if (words.is_open()) {
        std::istream_iterator<string> word_iter(words);
        while (!words.eof()) {
            out.push_back(remove_punct(*word_iter));
            ++word_iter;
        }
    }
    return out;
}
