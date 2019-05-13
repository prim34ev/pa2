/*
 * Name: Ajay Nair
 * Email: ajnair@ucsd.edu
 *
 * Program that makes use of BloomFilter to filter malicious URLs out of a list
 * of URLs in a file
 */

#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include "BloomFilter.hpp"

using namespace std;

size_t numURLs(string url_filename) {
  string line;
  size_t numLines = 0;
  ifstream reader(url_filename, ios::binary);

  if(reader.is_open()) {
    while(!reader.eof()) {
      getline(reader, line);
      if(line.length() > 1)
        numLines++;
    }
    reader.close();
  }

  return numLines;
}

size_t getFileSize(string filename) {
  ifstream reader(filename, ios::ate | ios::binary);
  size_t fileSize = 0;

  if(reader.is_open()) {
    fileSize = reader.tellg();
    reader.close();
  }

  return fileSize;
}

bool populateFilter(BloomFilter& filter, string url_filename) {
  ifstream reader(url_filename, ios::binary);
  if(!reader.is_open()) return false;

  string line;

  while(!reader.eof()) {
    getline(reader, line);
    if(line.length() > 1)
      filter.insert(line);
  }
  reader.close();

  return true;
}

/**
 * IMPORTANT! You should use the following lines of code to match the correct
 * output:
 * cout << "This program requires 3 arguments!" << endl;
 * 
 * arg1 - list of malicious urls/bad words filter out
 * arg2 - list of mixed (good/bad) to only write good urls to
 * arg3 - file to write only the good urls to (one on each line)
 */

int main(int argc, char** argv) {
  if(argc != 4) {
    cerr << "This program requires 3 arguments!" << endl;
    return EXIT_FAILURE;
  }

  unsigned int numBadURLs = numURLs(*(argv + 1));
  unsigned int numSafeURLs = 0;
  unsigned int numOutputs = 0;
  BloomFilter filter(ceil((double)numBadURLs * 3 / 2));
  ifstream in(*(argv + 2), ios::binary);
  ofstream out(*(argv + 3), ios::binary);
  string line;

  if(!(in.is_open() && out.is_open() && populateFilter(filter, *(argv + 1)))) {
    cerr << "Error opening input/output file(s)!" << endl;
    return EXIT_FAILURE;
  }

  while(!in.eof()) {
    getline(in, line);
    if(line.length() > 1) {
      if(!filter.find(line)) {
        out << line << endl;
        numOutputs++;
      }
      numSafeURLs++;
    }
  }
  in.close();
  out.close();
  numSafeURLs -= numBadURLs;

  double falsePositives = (double)(numSafeURLs - numOutputs) / numSafeURLs;
  double memoryRatio = (double)getFileSize(*(argv + 1)) / filter.size();

  cout << "False positive rate: " << falsePositives << endl;
  cout << "Saved memory ratio: " << memoryRatio << endl;

  return EXIT_SUCCESS;
}
