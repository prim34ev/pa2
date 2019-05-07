/*
 * Name: Ajay Nair
 * Email: ajnair@ucsd.edu
 *
 * Header file containing BloomFilter classes definition.
 */

#ifndef BLOOM_FILTER_HPP
#define BLOOM_FILTER_HPP

#include <string>

/**
 * The class for bloom filter that provides memory efficient check
 * of whether an item has been inserted before. Small amount of 
 * false positives is possible but there will be no false negatives.
 */
class BloomFilter {
  public:
    /* Create a new bloom filter with the size in bytes */
    BloomFilter(size_t numBytes);

    /* Insert an item into the bloom filter */
    void insert(std::string item);

    /* Determine whether an item is in the bloom filter */
    bool find(std::string item);

    size_t size();

    /* Destrctor for the bloom filter */
    ~BloomFilter();

  private:
    // The char array as the hash table
    const static unsigned int BYTE_WIDTH;
    const static unsigned int WORD_WIDTH;
    const static unsigned int CRC_HASH_SHIFT;
    const static unsigned int PJW_HASH_SHIFT;
    const static unsigned int PJW_HASH_RIGHT_SHIFT;
    const static unsigned int PJW_HASH_MASK;
    const static unsigned int BUZINIT;
    const static unsigned int BUZ_TABLE_SIZE;
    const static unsigned int BUZ_TABLE[256];

    unsigned char* table;
    unsigned int numSlots;

    unsigned int hashStringCRC(const std::string& key);
    unsigned int hashPJW(const std::string& key);
    unsigned int hashStringBUZ(const std::string& key);
    unsigned int hashBUZ(const unsigned char* key, int keylen);
};
#endif // BLOOM_FILTER
