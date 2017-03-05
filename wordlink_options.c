/****************************************************************************
* COSC2138/CPT220 - Programming Principles 2A
* SP2 2015 Assignment #2 - word link program
* Full Name        : Callum Michael Sullivan
* Student Number   : s3506523
* 
* Start up code provided by the C Teaching Team
****************************************************************************/

#include "wordlink.h"
#include "wordlink_options.h"
#include "wordlink_utility.h"

/****************************************************************************
* Menu option #1: 1 Player Game
* Game between human and computer controlled players.
* 
* Note: Additional modularisation is strongly recommended here.
* Extra candidate functions include playerGuess(), resetGame(), etc.
****************************************************************************/
void onePlayerGame(DictionaryType* dictionary)
{
   char lastChar = '\0';
   while(playerGuess(&lastChar,dictionary,"Player","YOUR MECHANISED OVERLORD")!= EXIT_FAILURE)
   { 
      if(computerGuess(&lastChar,dictionary) == EXIT_FAILURE)
      {
         break;
      }
   }
}

/******************************************************************************
* Prompts the player to guess a word and then evaluates if that guess is valid
*-returns EXIT_SUCCESS if it is.
*-returns EXIT_FAILURE if it isn't.
*-used in both single player and 2 player games
******************************************************************************/
int playerGuess(char *lastChar,DictionaryType* dictionary,char* player1Name,char * player2Name)
{
   char newGuess[MAX_WORD_LEN];
   int i = 0;
   while(i<MAX_WORD_LEN)
   {
      newGuess[i] = '\0';
      i++;
   }
   printf("%s%s", player1Name,": Enter a word (1-20 char, blank line to quit): ");
   fgets(newGuess,MAX_WORD_LEN,stdin);
   strtok(newGuess,"\n");
   if(newGuess[0] == '\n')
   {
      printf("%s\n","You entered a blank line to give up. Better luck next time.");
      return EXIT_FAILURE;
   }
   if(*lastChar != '\0' && tolower(newGuess[0]) != *lastChar)
   {
      printf("%s%s%s%c. %s%s\n","\"",newGuess,"\" does not start with ",*lastChar,player2Name,"  wins!");
      return EXIT_FAILURE;
   }
   if(searchWord(dictionary,newGuess,SYSTEM_SEARCH) == EXIT_SUCCESS)
   {
      *lastChar = getLastCharacter(newGuess);
      return EXIT_SUCCESS;
   }
   else
   {
      printf("%s%s%s%s%s\n","\"",newGuess,"\" is not in the dictionary. ",player2Name,"  wins!");
      return EXIT_FAILURE;
   }
}
/******************************************************************************
* The computer selects the first unused word in the linked list of the last 
*character of the last word guessed, then returns EXIT_SUCCESS
*-if there are no more unused words in said linked list it returns EXIT_FAILURE
*-used in single player games
******************************************************************************/
int computerGuess(char *lastChar,DictionaryType* dictionary)
{
   WordLinkTypePtr current = dictionary->headWords[*lastChar - 'a'];
   while(current->nextWord != NULL)
   {
      if(current->usedFlag == UNUSED)
      {
         current->usedFlag = USED;
         printf("%s%s\"\n","Computer selects word \"", current -> word);
         *lastChar = getLastCharacter(current->word);
         return EXIT_SUCCESS;
      }
      current = current -> nextWord;
   }
   printf("%s/n","Computer could not make a guess. You win!");
   return EXIT_FAILURE;
}
/******************************************************************************
* Searches the dictionary for a given word
*-returns EXIT_SUCCESS if that word is in the dictionary
*--if it is and the search mode is SYSTEM_SEARCH marks the word as USED
*-returns EXIT_FAILURE if it isn't
*-*-used in single player games, 2 player games and the search dictionary option
******************************************************************************/
int searchWord(DictionaryType* dictionary, char * searchedWord, unsigned searchType)
{
   WordLinkTypePtr current;
   int i = 0;
   if(!isalpha(searchedWord[0]) || (sizeof(searchedWord)/sizeof(searchedWord[0]))>MAX_WORD_LEN)
   {
     return EXIT_FAILURE;
   }
   while(i<MAX_WORD_LEN)
   {
      searchedWord[i] = tolower(searchedWord[i]);
      i++;
   }
   current = dictionary->headWords[searchedWord[0] - 'a'];
   while(current != NULL && strcmp(current->word,searchedWord) != 0)
   {
      current = current -> nextWord;
   }
   if(!current)
   {
      return EXIT_FAILURE;
   }
   if(searchType == SYSTEM_SEARCH)
   {
      if(current -> usedFlag == USED)
      {
         return EXIT_FAILURE;
      }
      else
      {
          current -> usedFlag = USED;
      }
   }
   return EXIT_SUCCESS;
}
/****************************************************************************
* Returns the last alphabet character of a word
*-returns ASCII NULL ('\0') if the word doesn't have any alphabet characters
****************************************************************************/
char getLastCharacter(char * word)
{
   char last = '\0';
   int i = 0;
   while(i<strlen(word))
   {
      if(isalpha(word[i]))
      {
         last = word[i];
      }
      i++;
   }
   return last;
}
/****************************************************************************
* Menu option #2: 2 Player Game
* Game between two human-controlled players.
* 
* Note: Additional modularisation is strongly recommended here.
* Extra candidate functions include playerGuess(), resetGame(), etc.
****************************************************************************/
void twoPlayerGame(DictionaryType* dictionary)
{
   char lastChar = '\0';
   while(playerGuess(&lastChar,dictionary,"Player One","Player Two")!= EXIT_FAILURE)
   { 
      if(playerGuess(&lastChar,dictionary,"Player Two","Player One") == EXIT_FAILURE)
      {
         break;
      }
   }
}


/****************************************************************************
* Menu option #3: Dictionary Summary
* Displays statistics on the words in the dictionary.
****************************************************************************/
void dictionarySummary(DictionaryType* dictionary)
{
   int i = 0;
   printf("%s\n", "+--------+--------+");
   while(i<ALPHABET_LEN/2)
   {
      printf("%c %c%c %u %c %c%c %u %c\n",'|', i+'a',':',dictionary->listCounts[i],'|',i+'a'+(ALPHABET_LEN/2),':',
      dictionary->listCounts[i+(ALPHABET_LEN/2)],'|');
      i++;
   }
   printf("%s\n", "+--------+--------+");
}


/****************************************************************************
* Menu option #4: Search Dictionary
* Prompts the user for a dictionary word and reports if the word is in the
* dictionary.
****************************************************************************/
void searchDictionary(DictionaryType* dictionary)
{
   char searchedWord[MAX_WORD_LEN];
   int i = 0;
   while(i<MAX_WORD_LEN)
   {
      searchedWord[i] = 0;
      i++;
   }
   printf("%s","Enter a word (1-20 char): ");
   fgets(searchedWord,MAX_WORD_LEN,stdin);
   if(searchedWord[0] == '\n')
   {
      return;
   }
   if(searchWord(dictionary,strtok(searchedWord,"\n"),PLAYER_SEARCH) == EXIT_SUCCESS)
   {
      printf("%s %s\n",strtok(searchedWord,"\n"), "IS in the dictionary");
   }
   else
   {
      printf("%s %s\n",strtok(searchedWord,"\n"), "is NOT in the dictionary");
   }
}


/****************************************************************************
* Menu option #5: Add Dictionary Word
* Prompts the user for a new dictionary word to be added to the data
* structure.
****************************************************************************/
void addDictionaryWord(DictionaryType* dictionary)
{
   char word[MAX_WORD_LEN];
   printf("%s","Enter a word (1-20 char): ");
   fgets(word,MAX_WORD_LEN,stdin);
   if(word[0] == '\n')
   {
      return;
   }
   strtok(word,"\n");
   if(wordIsAlpha(word)==EXIT_FAILURE || searchWord(dictionary,word,PLAYER_SEARCH) == EXIT_SUCCESS)
   {
      printf("%s%s\n",word," could not be added to the dictionary either because it is not alphanumeric or because it already is in the dictionary.");
   }
   else
   {
      addToDictionary(dictionary,word);
      printf("%s%s\n",word," has been added to the dictionary");
   }
}
/****************************************************************************
*Checks if every character in a word is either alphabetical or ASCII NULL.
*-returns EXIT_SUCCESS if it is.
*-returns EXIT_FAILURE if it isn't.
****************************************************************************/
int wordIsAlpha(char* word)
{
   int i = 0;
   while(i<strlen(word))
   {
      if(!isalpha(word[i]) && word[i] != '\0')
      {
         return EXIT_FAILURE;
      }
      i++;
   }
   return EXIT_SUCCESS;
}
/****************************************************************************
* Menu option #6: Save Dictionary
* Writes the contents of the dictionionary back to the original file.
****************************************************************************/
int saveDictionary(DictionaryType* dictionary, char* filename)
{
   DictionaryType sortedDictionary = sortDictionary(*dictionary);
   FILE * dictionaryFile;
   int i = 0;
   if(!(dictionaryFile = fopen(filename,"w")))
   {
      return EXIT_FAILURE;
   }
   while(i<ALPHABET_LEN)
   {
      WordLinkTypePtr current = sortedDictionary.headWords[i];
      while(current)
      {
         fprintf(dictionaryFile,"%s\n",current->word);
         current = current->nextWord;
      }
      i++;
   }
   fclose(dictionaryFile);
   return EXIT_SUCCESS;
}
/****************************************************************************
* Returns a dictionary sorted into alphabetical order
****************************************************************************/
DictionaryType sortDictionary(DictionaryType unsortedDictionary)
{
   DictionaryType sortedDictionary;
   int i = 0;
   systemInit(&sortedDictionary);
   while(i<ALPHABET_LEN)
   {
      WordLinkTypePtr currentUnsorted = unsortedDictionary.headWords[i];
      while(currentUnsorted)
      {
         WordLinkTypePtr currentSorted = sortedDictionary.headWords[i],previousSorted = NULL,newNode;
         while(currentSorted && wordIsGreater(currentUnsorted->word,currentSorted->word))
         {
            previousSorted = currentSorted;
            currentSorted = currentSorted->nextWord;
         }
         newNode = (WordLinkTypePtr)malloc(sizeof(WordLinkType));
         newNode->word = currentUnsorted->word;
         newNode->usedFlag = UNUSED;
         if(previousSorted)
         {
            newNode->nextWord = currentSorted;
            previousSorted->nextWord = newNode;
         }
         else
         {
            newNode->nextWord = currentSorted;
            sortedDictionary.headWords[i] = newNode;
         }
         currentUnsorted = currentUnsorted->nextWord;
      }
      sortedDictionary.listCounts[i] = unsortedDictionary.listCounts[i];
      i++;
   }
   sortedDictionary.totalWords = unsortedDictionary.totalWords;
   return sortedDictionary;
}
/****************************************************************************
* Returns TRUE if word 1 is greater than word 2, otherwise returns FALSE
****************************************************************************/
unsigned wordIsGreater(char* wordOne,char* wordTwo)
{
   int i = 0;
   while(i<strlen(wordOne) && i<strlen(wordTwo))
   {
      if(wordOne[i]-'a'>wordTwo[i]-'a')
      {
         return TRUE;
      }
      else if(wordOne[i]-'a'<wordTwo[i]-'a')
      {
         return FALSE;
      }
      i++;
   }
   if(strlen(wordOne)<strlen(wordTwo))
   {
      return FALSE;
   }
   else
   {
      return TRUE;
   }
}
