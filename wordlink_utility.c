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
* Function readRestOfLine() is used for buffer clearing. Blackboard source: 
* "Course Documents" > "FAQ" > "Alternative to non-standard fflush(stdin);"
****************************************************************************/
void readRestOfLine()
{
   int c;

   /* Read until the end of the line or end-of-file. */   
   while ((c = fgetc(stdin)) != '\n' && c != EOF)
      ;

   /* Clear the error and end-of-file flags. */
   clearerr(stdin);
}


/****************************************************************************
* Initialises the dictionary to a safe empty state.
****************************************************************************/
void systemInit(DictionaryType* dictionary)
{
   int i = 0;
   while(i<ALPHABET_LEN)
   {
      dictionary->listCounts[i] = 0;
      dictionary->headWords[i] = NULL;
      i++;
   }
   dictionary->totalWords = 0; 
}


/****************************************************************************
* Loads all data into the dictionary.
****************************************************************************/
int loadData(DictionaryType* dictionary, char* filename)
{
   char currentWord[20];
   FILE *dictionaryFile;
   if(!(dictionaryFile = fopen(filename,"r")))
   {
      return EXIT_FAILURE;
   }
   while(fgets(currentWord,MAX_WORD_LEN,dictionaryFile)!= NULL)
   {
      strtok(currentWord,"\n");
      addToDictionary(dictionary,currentWord);
   }
   fclose(dictionaryFile);
   return EXIT_SUCCESS;
}
/****************************************************************************
* Loads a single word into the dictionary.
****************************************************************************/
int addToDictionary(DictionaryType* dictionary, char* word)
{
   int listPos;
   int i = 0;
   WordLinkTypePtr current = dictionary->headWords[word[0] - 'a'],previous = NULL,new;
   srand(time(NULL));
   listPos = rand() % (dictionary->listCounts[word[0] - 'a'] + 1);
   while(i<listPos)
   {
      previous = current;
      current = current->nextWord;
      i++;
   }
      
   new = (WordLinkTypePtr)malloc(sizeof(WordLinkType));
   new->word = (char*)calloc(strlen(word)+1,sizeof(char));
   strcpy(new->word,word);
   new->usedFlag = UNUSED;
   new->nextWord = current;
   dictionary->listCounts[word[0] - 'a'] ++;
   if(previous == NULL)
   {
      dictionary->headWords[word[0] - 'a'] = new;
   }
   else
   {
      previous ->nextWord = new;
   }
   return EXIT_SUCCESS;
}
/****************************************************************************
* Deallocates memory used in the dictionary.
****************************************************************************/
void systemFree(DictionaryType* dictionary)
{
   if(dictionary)
   {
      int i = 0;
      while(i<ALPHABET_LEN)
      {
         WordLinkTypePtr current,previous;
         current = dictionary->headWords[i];
         while(current != NULL)
         {
            previous = current;
            current = current->nextWord;
            free(previous->word);
            free(previous);
         }
         dictionary->headWords[i] = NULL;
         i++;
      }
      free(dictionary);
   }
}
