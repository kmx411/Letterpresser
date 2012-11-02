#ifndef __TRIE_H__
#define __TRIE_H__
#include <string>
#include <vector>

struct TrieNode {
    enum { Apostrophe = 26, NumChars = 27 };
    bool isWord;
    TrieNode *letters[NumChars];
    TrieNode() {
        isWord = false;
         for ( int i = 0; i < NumChars; i += 1 ) {
             letters[i] = NULL;
         }//for
    }
}; // TrieNode

void insert( TrieNode &node, const std::string &word );

void remove( TrieNode &node, const std::string &word );

void find( TrieNode &node, std::string word, std::string wordSoFar );



#endif

