/**
 * @file word_counter.cpp
 * Implementation of the WordFreq class.
 *
 * @author Chase Geigle
 * @date Spring 2011
 * @date Spring 2012
 */
#include <iostream>

using std::vector;
using std::pair;
using std::string;
using std::ifstream;
using std::istringstream;
using std::cout;
using std::endl;

template <template <class K, class V> class Dict>
WordFreq<Dict>::WordFreq(const string &infile)
    : dict(256), filename(infile)
{
    /* nothing */
}

template <template <class K, class V> class Dict>
vector<pair<string, int>> WordFreq<Dict>::getWords(int threshold)
{
    int temp = 0;
    TextFile infile(filename);
    auto it = dict.begin();
    while (infile.good()) {
        string word = infile.getNextWord();
        if(!dict.keyExists(word)){
            dict.insert(word, 1);
        }
        else {
            dict[word]++;
        }
    }
    vector<pair<string, int>> ret;
    
    for (auto it = dict.begin(); it!=dict.end(); it++) {
        if (it->second >= threshold) {
            ret.push_back(*it);
        }
    }
    
    return ret;
}
