/*
 * Filename: DictionaryTrieNode.hpp
 * Author: Ajay Nair
 * Email: ajnair@ucsd.edu
 * Date: April 24, 2019
 *
 * Class declaration for DictionaryTrieNode, the nodes to be used when building
 * DictionaryTrie.
 */
#ifndef DICTIONARY_TRIE_NODE_HPP
#define DICTIONARY_TRIE_NODE_HPP

class DictionaryTrieNode {
  public:
    DictionaryTrieNode(char data);

    char getChar() const;
    bool isEOS() const;
    unsigned int getFrequency() const;
    unsigned int getMaxFrequency() const;
    DictionaryTrieNode* getLeft() const;
    DictionaryTrieNode* getRight() const;
    DictionaryTrieNode* nextDown() const;

    void setLeft(DictionaryTrieNode* left);
    void setRight(DictionaryTrieNode* right);
    void setNext(DictionaryTrieNode* down);
    void makeEOS(unsigned int freq);
    void setMaxFrequency(unsigned int maxFreq);

  private:
    char data;
    unsigned int freq;
    unsigned int maxFreq;
    DictionaryTrieNode* left;
    DictionaryTrieNode* down;
    DictionaryTrieNode* right;
};

#endif // DICTIONARY_TRIE_NODE_H
