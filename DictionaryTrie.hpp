/**
 *  CSE 100 PA2 C++ Autocomplete
 *  Authors: Jor-el Briones, Christine Alvarado, and Ajay Nair
 *  Email: ajnair@ucsd.edu
 *  Date: April 24, 2019
 *
 *  Class declaration for DictionaryTrie
 */

#ifndef DICTIONARY_TRIE_HPP
#define DICTIONARY_TRIE_HPP

#include "DictionaryTrieNode.hpp"
#include <vector>
#include <string>
#include <queue>
using namespace std;

struct SuffixData {
  std::string suffix;
  unsigned int freq;

  SuffixData(std::string suffix, unsigned int freq) : suffix(suffix),
                                                        freq(freq) {}
};

struct CompFreq {
  bool operator() (const SuffixData & s1, const SuffixData & s2) {
    return (s1.freq != s2.freq) ? s1.freq > s2.freq : s1.suffix < s2.suffix;
  }
};

typedef priority_queue<SuffixData, vector<SuffixData>, CompFreq> suffix_queue;

/**
 *  The class for a dictionary ADT, implemented as a trie
 *  You may implement this class as either a mulit-way trie
 *  or a ternary search trie, but you must use one or the other.
 */
class DictionaryTrie {
  public:

    /* Create a new Dictionary that uses a Trie back end */
    DictionaryTrie();

    /** 
     * Insert a word with its frequency into the dictionary.
     * Return true if the word was inserted, and false if it
     * was not (i.e. it was already in the dictionary or it was
     * invalid (empty string). This might be useful for testing
     * when you want to test a certain case, but don't want to
     * write out a specific word 300 times.
     */
    bool insert(std::string word, unsigned int freq);

    /* Return true if word is in the dictionary, and false otherwise. */
    bool find(std::string word) const;

    /* 
     * Return up to num_completions of the most frequent completions
     * of the prefix, such that the completions are words in the dictionary.
     * These completions should be listed from most frequent to least.
     * If there are fewer than num_completions legal completions, this
     * function returns a vector with as many completions as possible.
     * If no completions exist, then the function returns a vector of size 0.
     * The prefix itself might be included in the returned words if the prefix
     * is a word (and is among the num_completions most frequent completions
     * of the prefix)
     */
    std::vector<std::string>
           predictCompletions(std::string prefix, unsigned int num_completions);

    /* Return up to num_completions of the most frequent completions
     * of the pattern, such that the completions are words in the dictionary.
     * These completions should be listed from most frequent to least.
     * If there are fewer than num_completions legal completions, this
     * function returns a vector with as many completions as possible.
     * If no completions exist, then the function returns a vector of size 0.
     * The pattern itself might be included in the returned words if the pattern
     * is a word (and is among the num_completions most frequent completions
     * of the pattern)
     */
    std::vector<std::string>
           predictUnderscore(std::string pattern, unsigned int num_completions);

    /* Destructor */
    ~DictionaryTrie();

  private:
    DictionaryTrieNode* root;
    bool found;
    suffix_queue completions;
    unsigned int numPredict;


    void deleteAll(DictionaryTrieNode* node);

    DictionaryTrieNode* insert(std::string word, unsigned int freq,
                               DictionaryTrieNode* curNode, unsigned int i);

    bool find(std::string word, DictionaryTrieNode* curNode, 
                                unsigned int i) const;

    DictionaryTrieNode* traverseTo(std::string word,
                                   DictionaryTrieNode* curNode,
                                   unsigned int i) const;

    void findCompletions(DictionaryTrieNode* node, std::string curSuffix);
    
    void updateQueue(std::string suffix, unsigned int freq);
};

#endif // DICTIONARY_TRIE_H
