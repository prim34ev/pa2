/*
 * Filename: autocomplete.cpp
 * Author: Ajay Nair
 * Email: ajnair@ucsd.edu
 * Date: April 25, 2019
 *
 * Program that will allow the user to fill a DictionaryTrie with the contents
 * of a dictionary, and then run a basic autocomplete search using the stored
 * frequency data and a user-given pattern.
 */
#include "util.hpp"
#include "DictionaryTrie.hpp"
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdlib>

using namespace std;

void generateDict(string dict_filename, DictionaryTrie& dictionary_trie) {
  ifstream in(dict_filename, ios::binary);

  cout << "Reading file: " << dict_filename << endl;
  Utils::load_dict(dictionary_trie, in);

  in.close();
}

void interact(DictionaryTrie* dict) {
  char searchAgain;
  string input;
  string prefix;
  unsigned int numCompletions;
  vector<string> completions;
  vector<string>::iterator it;
  do {
    cout << "Enter a prefix/pattern to search for:" << endl;
    getline(cin, prefix);
    cout << "Enter a number of completions:" << endl;
    getline(cin, input);
    istringstream(input) >> numCompletions;
    if(prefix.find('_') != string::npos) {
      completions = dict->predictUnderscore(prefix, numCompletions);
    }
    else {
      completions = dict->predictCompletions(prefix, numCompletions);
    }
    for(it = completions.begin(); it != completions.end(); it++) {
      cout << *it << endl;
    }
    completions.clear();
    cout << "Continue? (y/n)" << endl;
    getline(cin, input);
    istringstream(input) >> searchAgain;
  } while(searchAgain == 'y');
}
/**
 * IMPORTANT! You should use the following lines of code to match the correct output:
 * 
 * cout << "This program needs exactly one argument!" << endl;
 * cout << "Reading file: " << file << endl;
 * cout << "Enter a prefix/pattern to search for:" << endl;
 * cout << "Enter a number of completions:" << endl;
 * cout << completion << endl;
 * cout << "Continue? (y/n)" << endl;
 * 
 * arg 1 - Input file name (in format like freq_dict.txt)
 */
int main(int argc, char** argv) {
  if(argc != 2) {
    cerr << "This program needs exactly one argument!" << endl;
    return EXIT_FAILURE;
  }

  DictionaryTrie* dict;
  generateDict(argv[1], *(dict = new DictionaryTrie()));
  interact(dict);

  delete dict;

  return EXIT_SUCCESS;
}
