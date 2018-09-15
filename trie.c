#include "trie.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int char_to_index(char c){
  char espacio = ' ';
  if (espacio == c) {
    return 26;
  }
  return ((int)c - (int)'a');
}


Trie *trie_init()
{
  Trie* trie = malloc(sizeof(Trie));
  trie -> is_end = false;
  trie -> longest_int = 0;
  if (trie)
    {
        int i;
        for (i = 0; i < ALPHABET_SIZE; i++)
            trie->children[i] = NULL;
    }
  return trie;
}


void insert(Trie* trieTree, char word[], int freq, int length)
  {
    // We declare a pointer to the root or node given
    Trie* current = trieTree;
    if (current->longest_int <= freq) {
      current->longest_int = freq;
      strcpy(current->longest_word, word);
    }

    // While we havent finished all the letters in word
    for (int i = 0; i < length; i++) {
      int indexar = char_to_index(word[i]);
      // If children not created, we create it and set parent
      if (current->children[indexar] == NULL) {
        current->children[indexar] = trie_init();
      }
      current = current->children[indexar];
      if (current->longest_int <= freq) {
        current->longest_int = freq;
        strcpy(current->longest_word, word);
      }
    }
    current->is_end = true;
  }


char* suggest(Trie* trieTree, char word[], int length)
{
  // Chequeo si me entregaron un str vacio y retorno mayor
    Trie* current = trieTree;

    for (int i = 0; i < length; i++) {
      int indexar = char_to_index(word[i]);
      if (current->children[indexar] != NULL) {
        current = current->children[indexar];
      }
      else {
        return word;
      }
    }
    return current->longest_word;
  }


void destroy_all(Trie* trieTree){
  Trie* current = trieTree;
  bool is_leaf = true;
  for(int i = 0; i < ALPHABET_SIZE; i++){
    if (current->children[i] != NULL) {
      is_leaf = false;
    }
  }
  if (is_leaf) {
    free(current);
  }
  else{
    for (int i = 0; i < ALPHABET_SIZE; i++) {
      if (current->children[i] != NULL) {
        destroy_all(current->children[i]);
      }
    }
    free(current);
  }
}
