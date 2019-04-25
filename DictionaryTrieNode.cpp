#include "DictionaryTrieNode.hpp"

DictionaryTrieNode::DictionaryTrieNode(
                                   char data, unsigned int freq) : data(data),
                                                                   freq(freq),
                                                                left(nullptr),
                                                                down(nullptr),
                                                               right(nullptr) {}

char DictionaryTrieNode::getChar() const {
  return this->data;
}

bool DictionaryTrieNode::isEOS() const {
  return this->freq > 0;
}

unsigned int getFrequency() const {
  return this->freq;
}

DictionaryTrieNode* DictionaryTrieNode::getLeft() const {
  return this->left;
}

DictionaryTrieNode* DictionaryTrieNode::getRight() const {
  return this->right;
}

DictionaryTrieNode* DictionaryTrieNode::nextDown() const {
  return this->next;
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
