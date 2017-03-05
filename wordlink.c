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

int main(int argc, char* argv[])
{
   int selection;
   DictionaryType* dictionary = malloc(sizeof(DictionaryType));
   if(argc != 2)
   {
      printf("%s\n%s\n","Error: no filename entered.","Program terminating");
      return EXIT_FAILURE;
   }
   systemInit(dictionary);
   if(loadData(dictionary,argv[1]) == EXIT_FAILURE)
   {
      printf("%s\n%s\n","Error: no such file exists in the current directory.","Program terminating");
      return EXIT_FAILURE;
   }
   do{
   printf("%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n\n%s","Main Menu:","(1) 1 Player Game","(2) 2 Player Game","(3) Dictionary Summary",
   "(4) Search Dictionary", "(5) Add Dictionary Word","(6) Save Dictionary","(7) Exit","(8) Abort","Select your option (1-7): ");
   selection = getchar() - '0';
   readRestOfLine();
   switch(selection)
   {
   case 1:
      printf("%s\n%s\n\n","1 Player Game","-------------");
      systemFree(dictionary);
      dictionary = (DictionaryType*)malloc(sizeof(DictionaryType));
      systemInit(dictionary);
      loadData(dictionary,argv[1]);
      onePlayerGame(dictionary);
      break;
   case 2:
      printf("%s\n%s\n\n","2 Player Game","-------------");
      systemFree(dictionary);
      dictionary = (DictionaryType*)malloc(sizeof(DictionaryType));
      systemInit(dictionary);
      loadData(dictionary,argv[1]);
      twoPlayerGame(dictionary);
      break;
   case 3:
      printf("%s\n%s\n\n","Dictionary Summary","------------------");
      dictionarySummary(dictionary);
      break;
   case 4:
      printf("%s\n%s\n\n","Search Dictionary","------------------");
      searchDictionary(dictionary);
      break;
   case 5:
      printf("%s\n%s\n\n","Add Dictionary Word","-----------------");
      addDictionaryWord(dictionary);
      break;
   case 6:
      printf("%s\n%s\n\n","Save Dictionary","---------------");
      if((saveDictionary(dictionary,argv[1]))==EXIT_SUCCESS)
      {
         printf("%s\n","Dictionary succesfully saved.");
      }
      else
      {
          printf("%s\n","An error occured while attempting to save the dictionary.");
      }
      break;
   default:
      break;
   }
   }while(selection != 7 && selection != 8);
   if(selection == 7)
   {
      saveDictionary(dictionary,argv[1]);
   }
   systemFree(dictionary);
   return EXIT_SUCCESS;
}
