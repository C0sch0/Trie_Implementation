#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX_LENGTH 101
#define ALPHABET_SIZE 27
#define CASE 'a'

// Definir struct aca

// Trie node
struct Trie_Node
{
     struct Trie_Node *children[ALPHABET_SIZE];
     bool is_end;
     char longest_word[MAX_LENGTH];
     int longest_int;
};

typedef struct Trie_Node Trie;

// Headers de funciones aca
void insert(Trie* trieTree, char* word, int freq, int length);
void destroy_all(Trie* trieTree);
char* suggest(Trie* trieTree, char* word, int length);
Trie *trie_init();
