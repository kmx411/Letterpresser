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

struct State
{
    State (std::string topermute_, int place_, int nextchar_, State* next_ = 0)
        : topermute (topermute_)
        , place (place_)
        , nextchar (nextchar_)
        , next (next_)
    {
    }

    std::string topermute;
    int place;
    int nextchar;

    State* next;
};

std::string swtch (std::string topermute, int x, int y)
{
    std::string newstring = topermute;
    newstring[x] = newstring[y];
    newstring[y] = topermute[x]; //avoids temp variable

    return newstring;
}

void permute (std::string topermute,TrieNode &dictionary, int place = 0 )
{
    // Linked list stack.
    State* top = new State (topermute, place, place);

    while (top != 0)
    {
        State* pop = top;
        top = pop->next;

        if (pop->place == pop->topermute.length () - 1)
        {
            find( dictionary, pop->topermute, "" );
        }

        for (int i = pop->place; i < pop->topermute.length (); ++i)
        {
            top = new State (swtch (pop->topermute, pop->place, i), pop->place + 1, i, top);
        }

        delete pop;
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

  ifstream myfile( "letterpress_dictionary.txt" );
  while( myfile >> item ){
    checkFunction( *dictionary, "+", item );
  }
  myfile.close();

  while( cin >> in ){

    for( int i = 0; i <= in.size(); i++ ){
      permute( in.substr(0,i), *dictionary );
    }
  }

  deletePointers( dictionary );

  return 0;
}

