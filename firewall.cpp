#include <iostream>
#include <fstream>
#include <cmath>
#include "BloomFilter.hpp"

using namespace std;

size_t numURLs(string url_filename) {
  string line;
  ifstream reader;
  size_t numLines = 0;

  reader.open(url_filename, ios::binary);

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
  ifstream reader;
  size_t fileSize;

  reader.open(filename, ios::ate | ios::binary);
  fileSize = reader.tellg();

  reader.close();

  return fileSize;
}

void populateFilter(BloomFilter* filter, string url_filename) {
  string line;
  ifstream reader;

  reader.open(url_filename, ios::binary);

  if(reader.is_open()) {
    while(!reader.eof()) {
      getline(reader, line);
      if(line.length() > 1)
        filter->insert(line);
    }
    reader.close();
  }
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
    cout << "This program requires 3 arguments!" << endl;
    return 1;
  }

  unsigned int numBadURLs = numURLs(argv[1]);
  unsigned int numSafeURLs = 0;
  unsigned int numOutputs = 0;
  BloomFilter filter = BloomFilter(ceil((double)numBadURLs * 3 / 2));

  string line;
  ifstream reader;
  ofstream outFile;

  populateFilter(&filter, argv[1]);
  reader.open(argv[2], ios::binary);
  outFile.open(argv[3], ios::binary);

  if(reader.is_open() && outFile.is_open()) {
    while(!reader.eof()) {
      getline(reader, line);
      if(line.length() > 1) {
        if(!filter.find(line)) {
          outFile << line << endl;
          numOutputs++;
        }
        numSafeURLs++;
      }
    }
    numSafeURLs -= numBadURLs;

    reader.close();
    outFile.close();
  }
  else
    return 1;

  double falsePositives = (double)(numSafeURLs - numOutputs) / numSafeURLs;
  double memoryRatio = (double)getFileSize(argv[1]) / filter.size();

  cout << "False positive rate: " << falsePositives << endl;
  cout << "Saved memory ratio: " << memoryRatio << endl;

  return 0;
}
