#include "DictionaryTrieNode.hpp"

DictionaryTrieNode::DictionaryTrieNode(char data): data(data), freq(0),
                                                   left(nullptr), down(nullptr),
                                                   right(nullptr) {}

char DictionaryTrieNode::getChar() const {
  return this->data;
}

bool DictionaryTrieNode::isEOS() const {
  return this->freq > 0;
}

unsigned int DictionaryTrieNode::getFrequency() const {
  return this->freq;
}

DictionaryTrieNode* DictionaryTrieNode::getLeft() const {
  return this->left;
}

DictionaryTrieNode* DictionaryTrieNode::getRight() const {
  return this->right;
}

DictionaryTrieNode* DictionaryTrieNode::nextDown() const {
  return this->down;
}

void DictionaryTrieNode::setLeft(DictionaryTrieNode* left) {
  this->left = left;
}

void DictionaryTrieNode::setRight(DictionaryTrieNode* right) {
  this->right = right;
}

void DictionaryTrieNode::setNext(DictionaryTrieNode* down) {
  this->down = down;
}

void DictionaryTrieNode::makeEOS(unsigned int freq) {
  this->freq = freq;
}
