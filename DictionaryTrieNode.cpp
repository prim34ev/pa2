/*
 * Filename: DictionaryTrieNode.cpp
 * Author: Ajay Nair
 * Email: ajnair@ucsd.edu
 * Date: April 25, 2019
 *
 * Definitions for all DictionaryTrieNode member functions, including its
 * constructor.
 */
#include "DictionaryTrieNode.hpp"

DictionaryTrieNode::DictionaryTrieNode(char data): data(data), freq(0),
                                                   maxFreq(0), left(nullptr),
                                                   down(nullptr), right(nullptr)
                                                                              {}

char DictionaryTrieNode::getChar() const {
  return this->data;
}

bool DictionaryTrieNode::isEOS() const {
  return this->freq > 0;
}

unsigned int DictionaryTrieNode::getFrequency() const {
  return this->freq;
}

unsigned int DictionaryTrieNode::getMaxFrequency() const {
  return this->maxFreq;
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

void DictionaryTrieNode::setMaxFrequency(unsigned int maxFreq) {
  this->maxFreq = maxFreq;
}
