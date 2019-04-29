/*
 * Filename: DictionaryTrie.cpp
 * Author: Ajay Nair
 * Email: ajnair@ucsd.edu
 * Date: April 24, 2019
 *
 * Implementation of a ternary search trie to store the contents of a
 * dictionary.
 */
#include "DictionaryTrie.hpp"

/* Create a new Dictionary that uses a Trie back end */
DictionaryTrie::DictionaryTrie(): root(nullptr),
                                  completions(suffix_queue(CompFreq())),
                                  numPredict(0) {}

/**
 * Insert a word with its frequency into the dictionary.
 * Return true if the word was inserted, and false if it
 * was not (i.e. it was already in the dictionary or it was
 * invalid (empty string). This might be useful for testing
 * when you want to test a certain case, but don't want to
 * write out a specific word 300 times.
 */
bool DictionaryTrie::insert(std::string word, unsigned int freq) {
  if(word.empty() || freq == 0) return false;

  bool found = false;

  this->root = this->insert(word, freq, this->root, 0, &found);
  return !found;
}


/* Return true if word is in the dictionary, and false otherwise */
bool DictionaryTrie::find(std::string word) const {
  if(word.empty()) return false;

  return this->find(word, this->root, 0);
}


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
std::vector<std::string> DictionaryTrie::predictCompletions(
                             std::string prefix, unsigned int num_completions) {
  DictionaryTrieNode* prefixEnd;
  if(!(prefixEnd = this->find(prefix, this->root, 0)) ||
                                                num_completions == 0) return {};

  this->numPredict = num_completions;
  if(prefixEnd->isEOS()) {
    this->updateQueue("", prefixEnd->getFrequency());
  }

  this->findCompletions(prefixEnd->nextDown(), "");

  std::vector<std::string> fullCompletions;
  while(!this->completions.empty()) {
    fullCompletions.insert(fullCompletions.begin(),
                           prefix + this->completions.top().first);
    this->completions.pop();
  }
  return fullCompletions;
}

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
std::vector<std::string> DictionaryTrie::predictUnderscore(
                            std::string pattern, unsigned int num_completions) {
  return {};
}

/* Destructor */
DictionaryTrie::~DictionaryTrie() {
  this->deleteAll(this->root);
  this->root = nullptr;
}

void DictionaryTrie::deleteAll(DictionaryTrieNode* node) {
  if(!node) return;

  this->deleteAll(node->getLeft());
  node->setLeft(nullptr);

  this->deleteAll(node->nextDown());
  node->setNext(nullptr);

  this->deleteAll(node->getRight());
  node->setRight(nullptr);

  delete node;
}

DictionaryTrieNode* DictionaryTrie::insert(
                                  std::string word, unsigned int freq,
                                  DictionaryTrieNode* curNode, unsigned int i,
                                  bool* found) {
  if(!curNode) {
    curNode = new DictionaryTrieNode(word[i]);
  }

  if(word[i] < curNode->getChar()) {
    curNode->setLeft(this->insert(word, freq, curNode->getLeft(), i, found));
  }
  else if(word[i] > curNode->getChar()) {
    curNode->setRight(this->insert(word, freq, curNode->getRight(), i, found));
  }
  else if(i + 1 < word.length()) {
    curNode->setNext(this->insert(word, freq, curNode->nextDown(), i + 1, 
                                  found));
  }
  else if(!(*found = curNode->isEOS())) {
    curNode->makeEOS(freq);
  }

  return curNode;
}

DictionaryTrieNode* DictionaryTrie::find(
          std::string word, DictionaryTrieNode* curNode, unsigned int i) const {
  if(!curNode) return nullptr;

  if(word[i] < curNode->getChar()) {
    return this->find(word, curNode->getLeft(), i);
  }

  if(word[i] > curNode->getChar()) {
    return this->find(word, curNode->getRight(), i);
  }

  if(i + 1 < word.length()) {
    return this->find(word, curNode->nextDown(), i + 1);
  }

  return curNode;
}

void DictionaryTrie::findCompletions(
                              DictionaryTrieNode* node, std::string curSuffix) {
  if(!node) return;

  this->findCompletions(node->getLeft(), curSuffix);

  if(node->isEOS()) {
    this->updateQueue(curSuffix + node->getChar(), node->getFrequency());
  }

  this->findCompletions(node->nextDown(), curSuffix + node->getChar());
  this->findCompletions(node->getRight(), curSuffix);
}

void DictionaryTrie::updateQueue(std::string suffix, unsigned int freq) {
  this->completions.push(std::pair<std::string, unsigned int>(suffix, freq));
  if(this->completions.size() > this->numPredict) {
    this->completions.pop();
  }
}
