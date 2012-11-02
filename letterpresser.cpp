#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <fstream>
#include "letterpresser.h"

using namespace std;


void insert( TrieNode &node, const std::string &word ){
    int letter = word[0];
    int index = letter - 97;


    if( node.letters[index] != NULL) {

      if( word.size() == 1 ){
        node.letters[index]->isWord = true; 
        return;
      }

      insert( *(node.letters[index]), word.substr(1, word.size() - 1));
    }

    else { 
      if( word.size() == 1 ){ 
        node.letters[index] = new TrieNode; 
        node.letters[index]->isWord = true;
        return;
      } 

      node.letters[index] = new TrieNode; // make a node
      insert( *(node.letters[index]), word.substr(1, word.size() - 1));//recursee
    }
}

void remove( TrieNode &node, const std::string &word ) {
    int letter = word[0]; 
    int index = letter - 97;


    if( node.letters[index] != NULL) {
      if( word.size() == 1 ){ 
        node.letters[index]->isWord = false;
        return;
      }
      remove( *(node.letters[index]), word.substr(1, word.size() - 1));
    }

    else { 
      return; // do nothing
    }
}

void find(  TrieNode &node, string word, string wordSoFar ) {
    if (word.length() >= 1) {
      int letter = word[0];
      int index = letter - 97;

      if( node.letters[index] != NULL ) {
        if( word.length() == 1 && node.letters[index]->isWord) cout << wordSoFar << word[0] << " "; 

        find( *(node.letters[index]), word.substr(1, word.length() - 1), wordSoFar + word[0]); // call again

      }

    }
}

void checkFunction( TrieNode &dictionary, string ch, string word ) {
    string blank = "";

    if( ch == "+" ){
      insert( dictionary, word );
    }

    if(ch == "-"){
      remove( dictionary, word );
    }

    if(ch == "?") { 
      find( dictionary, word, blank );
      cout << endl;
    }
}

void deletePointers( TrieNode *dictionary ){
  for( int i = 0; i < 26; i++ ){
    if( dictionary->letters[i] != NULL ) deletePointers( dictionary->letters[i] );
  }

  delete dictionary;
}

int main() {
  TrieNode* dictionary = new TrieNode();
  string blank = "";
  string word;
  string in;
  string oper;
  string item;

  //ifstream myfile( "letterpress_by_length.txt" );
  //while( myfile >> item ){
    //checkFunction( *dictionary, "+", item );
  //}
  //myfile.close();

  while( cin >> in ){
    cin >> word;
    string line;


    if( in == "include" ){
      ifstream myfile( word.c_str() );
      while( myfile >> oper >> item ){
        checkFunction( *dictionary, oper, item );
      }
      myfile.close();
    }

    else  checkFunction( *dictionary, in, word );
  }

  deletePointers( dictionary );

  return 0;
}

