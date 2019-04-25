#ifndef DICTIONARY_TRIE_NODE_HPP
#define DICTIONARY_TRIE_NODE_HPP

using namespace std;

class DictionaryTrieNode {
  private:
    char data;
    unsigned int freq;
    DictionaryTrieNode* left;
    DictionaryTrieNode* down;
    DictionaryTrieNode* right;

  public:
    DictionaryTrieNode(char data, unsigned int freq = 0);

    char getChar() const;
    bool isEOS() const;
    unsigned int getFrequency() const;
    DictionaryTrieNode* getLeft() const;
    DictionaryTrieNode* getRight() const;
    DictionaryTrieNode* nextDown() const;

    void setLeft(DictionaryTrieNode* left);
    void setRight(DictionaryTrieNode* right);
    void setNext(DictionaryTrieNode* down);
    void makeEOS(unsigned int freq);
};

#endif // DICTIONARY_TRIE_NODE_H
