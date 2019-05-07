#include "BloomFilter.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

const unsigned int DEFAULT_SIZE = 5;
const unsigned int RESIZE_FACTOR = 2;
const double MAX_LOAD_FACTOR = 0.67;
const unsigned int BYTE_WIDTH = 8;
const unsigned int WORD_WIDTH = sizeof(int) * BYTE_WIDTH;
const unsigned int CRC_HASH_SHIFT = 5;
const unsigned int PJW_HASH_SHIFT = 4;
const unsigned int PJW_HASH_RIGHT_SHIFT = 24;
const unsigned int PJW_HASH_MASK = 0xF0000000;
const unsigned int PREISS_HASH_SHIFT = 6;
const unsigned int PREISS_HASH_MASK = ~0U << (WORD_WIDTH - PREISS_HASH_SHIFT);
const unsigned int WEISS_HASH_SHIFT = 5;
const unsigned int WEISS_HASH_MULTIPLIER = 37;

// stores number of inserted items in each slot
vector<unsigned int> table(DEFAULT_SIZE);

// stores all the hash value of inserted items
vector<unsigned int> inserted;

unsigned int tableLen = DEFAULT_SIZE;
unsigned int numElem = 0;

/** The hash function that we are testing for collisions */
unsigned int hashFunc(const std::string & item) {
  // TODO: add the hash function you found here
  unsigned int hashValue = 0;
  for(string::const_iterator it = item.begin(); it != item.end(); it++) {
    hashValue = (hashValue << BYTE_WIDTH) + (unsigned)*it;
    hashValue %= table.size();
  }
  return hashValue;
}

/** Returns the number of collisions in the hash table */
unsigned int countCollision() {
  unsigned int numCollisions = 0;
  vector<unsigned int>::iterator it;
  for(it = table.begin(); it != table.end(); it++) {
    if(*it > 1)
      numCollisions++;
  }
  return numCollisions;
}

/** When load factor is high, rehash all the inserted items */
void rehash() {

  // print out the stats before each rehash
  std::cout << "#insertions: " << numElem
    << "; hash table size: " << tableLen
    << "; #collisions: " << countCollision() << std::endl;

  tableLen = tableLen * RESIZE_FACTOR;
  table.clear();
  table.resize(tableLen);
  // rehash all the inserted items
  for (unsigned int hashVal: inserted) {
    table[hashVal % tableLen]++;
  }
}

/** "Insert" a given item to hash table. This function does not 
 *  actually insert the item, it only increases the count of number
 *  of items inserted in the hashed slot.
 */
void insert(const std::string & item) {

  // rehash if load factor is high
  if ((double) numElem / tableLen >= MAX_LOAD_FACTOR) {
    rehash();
  }
  unsigned int hashVal = hashFunc(item);
  table[hashVal % tableLen]++;
  numElem++;
  inserted.push_back(hashVal);
}

int main(int argc, const char * argv[]) {

  // reads the file line by line and insert each line to hash 
  // table to output stats about the hash function
  ifstream items (argv[1]);
  string line;

  while (true) {
    getline(items, line);
    if (items.eof()) break;
    insert(line);
  }
}

