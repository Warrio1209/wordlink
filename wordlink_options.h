/****************************************************************************
* COSC2138/CPT220 - Programming Principles 2A
* SP2 2015 Assignment #2 - word link program
* Full Name        : Callum Michael Sullivan
* Student Number   : s3506523
* 
* Start up code provided by the C Teaching Team
****************************************************************************/
/*Unique constant definitions*/
#ifndef WORDLINK_OPTIONS_H
#define WORDLINK_OPTIONS_H

/*Unique header files*/
#include <ctype.h>

/* Function prototypes. */
void onePlayerGame(DictionaryType* dictionary);
int playerGuess(char *lastChar,DictionaryType* dictionary,char* player1Name,char * player2Name);
int computerGuess(char *lastChar,DictionaryType* dictionary);
char getLastCharacter(char * word);
void twoPlayerGame(DictionaryType* dictionary);
void dictionarySummary(DictionaryType* dictionary);
void searchDictionary(DictionaryType* dictionary);
void addDictionaryWord(DictionaryType* dictionary);
int wordIsAlpha(char* word);
int saveDictionary(DictionaryType* dictionary, char* filename);
int searchWord(DictionaryType* dictionary, char * searchedWord, unsigned searchType);
DictionaryType sortDictionary(DictionaryType unsortedDictionary);
unsigned wordIsGreater(char* wordOne,char* wordTwo);
#endif
