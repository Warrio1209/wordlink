/****************************************************************************
* COSC2138/CPT220 - Programming Principles 2A
* SP2 2015 Assignment #2 - word link program
* Full Name        : Callum Michael Sullivan
* Student Number   : s3506523
* 
* Start up code provided by the C Teaching Team
****************************************************************************/
/* Unique header files*/
#include <time.h>

/*Constant definitions*/
#ifndef WORDLINK_UTILITY_H
#define WORDLINK_UTILITY_H
#define MAX_WORD_LENGTH 20

/* Function prototypes. */
void readRestOfLine();
void systemInit(DictionaryType* dictionary);
int loadData(DictionaryType* dictionary, char* filename);
void systemFree(DictionaryType* dictionary);
int addToDictionary(DictionaryType* dictionary, char* word);
#endif
