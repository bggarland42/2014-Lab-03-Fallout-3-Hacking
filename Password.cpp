#include "Password.h"
using CSC2110::ListArrayIterator;

#include <iostream>
using namespace std;



Password::Password()
{
  ListArray<String> viable_words = ListArray<String>();

  ListArray<String> all_words = ListArray<String>();

  len = 0;
 }

Password::~Password()
{
   ListArrayIterator<String>* iter = viable_words->iterator();
   
   while(iter->hasNext())
   {
     String* string = iter->next();
     delete string;
     }

    delete iter;

    delete viable_words;
    viable_words = NULL;

   ListArrayIterator<String>* iter_2 = all_words->iterator();  

   while(iter_2->hasNext())
   {
     String* orig_words = iter_2->next();
     delete orig_words;
     }

    delete iter_2;

    delete all_words;
    all_words = NULL;

 }

void Password::addWord(String* word)
{
  if(len == 0)
  {
    len = word->length();
    }

  if(len == word->length())
   {
     all_words->add(word);
    
     viable_words->add(word);
      
    }


 }

int Password::getNumMatches(String* curr_word, String* word_guess)
{
   int matches = 0;

   for(int i = 0; i < len; i++)
   {
      char curr_word_char = curr_word->charAt(i);
      char word_guess_char = word_guess->charAt(i);

      if(curr_word_char == word_guess_char)
       {
           matches++;

         }


     }

  return matches;
  }

void Password::guess(int try_password, int num_matches)
{
   String* guessed_word = all_words->get(try_password);

   int all_words_size = all_words->size();

   for(int i = 1; i <= all_words_size; i++)
   { 


     }


 }

int Password::getNumberOfPasswordsLeft()
{

 }

void Password::displayViableWords()
{
 
 }

String* Password::getOriginalWord(int index)
{

 }


int Password::bestGuess()
{
   int best_guess_index = -1;
   int best_num_eliminated = -1;
   int num_viable_passwords = getNumberOfPasswordsLeft();

   //loop over ALL words, even if they have been eliminated as the password
   int count = 1;
   ListArrayIterator<String>* all_iter = all_words->iterator();
   while(all_iter->hasNext())
   {
      String* original_word = all_iter->next();

      //loop over only those words that could still be the password
      //count up the number of matches between a possible password and a word in the original list
      int* count_num_matches = new int[len + 1];

      for (int i = 0; i < len; i++) 
      {
         count_num_matches[i] = 0;
      }

      ListArrayIterator<String>* viable_iter = viable_words->iterator();
      while(viable_iter->hasNext())
      {
         String* viable_word = viable_iter->next();
         int num_matches = getNumMatches(viable_word, original_word);
         count_num_matches[num_matches]++;
      }
      delete viable_iter;

      //find the largest number in the count_num_matches array
      //the largest number indicates the guess that will generate the most eliminations
      int most_num_matches = 0;
      for (int j = 0; j < len; j++) 
      {
         int curr_num_matches = count_num_matches[j];
         if (curr_num_matches > most_num_matches)
         {
            most_num_matches = curr_num_matches;
         }
      }

      //compute the fewest that can possibly be eliminated by guessing the current word (original list)
      int num_eliminated = num_viable_passwords - most_num_matches;

      //select the word to guess that maximizes the minimum number of eliminations (minimax)
      if (num_eliminated > best_num_eliminated)
      {
         best_num_eliminated = num_eliminated;
         best_guess_index = count;
      }
      
      count++;
      delete[] count_num_matches;
   }

   delete all_iter;
   return best_guess_index;  //return a 1-based index into the all_words list of words (careful)
}
