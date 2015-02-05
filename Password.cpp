#include "Password.h"
#include "ListArray.h"
#include "Text.h"
#include "ListArrayIterator.h"


#include <iostream>
using namespace std;
using CSC2110::ListArrayIterator;
using CSC2110::String;
using CSC2110::ListArray;


Password::Password()
{
	viable_words = new ListArray<String>();
	all_words = new ListArray<String>();
}

Password::~Password()
{
	//We use the regular delete right(?), not the array delete since we are deleting a pointer to a listarray object.
	//Is this right or a for loop? Ask Boshart CL
	delete[] viable_words;
	delete[] all_words;
}

void Password::addWord(String* word)
{
	//I'm not sure that this is the most efficient way to do this. I checked to see if there was anything at index 0. If not, then the length was logged. Any suggestions?? --KEB
	if(all_words->size() == 0)
	{
		len = word->length();
	}
	
	//We had to check if the current word had the same length as the first word, right? If not, remove the check. --KEB
	if(word->length() == len)
	{
		viable_words->add(word);
		all_words->add(word);
	}
	
}

void Password::guess(int try_password, int num_matches)
{
	//remove try_password-1 from list

	
	
	ListArray<String>* new_viable_words = new ListArray<String>;
	
	int num_matches_in_word = 0;
	//copy the attempted password --KEB
	String* attempted_password = all_words->get(try_password);
	// This is the an iterator of viable words, right? I can't remember what he said, but it makes since. --KEB
	ListArrayIterator<String>* viable_pass_iterator = viable_words->iterator();
	while(viable_pass_iterator->hasNext())
	{
		String* current_word = viable_pass_iterator->next();
		//I have no doubt that an iterator can be used here, but I'm not sure how since the text array in string is a single pointer. Any suggestions? --KEB
		num_matches_in_word = getNumMatches(current_word, attempted_password);
		//I am assuming num_matches is equal to the number alike characters at i --KEB
		if(num_matches_in_word == num_matches)
		{
			new_viable_words->add(current_word);
			
		}
		
		num_matches_in_word = 0;
	}
	
	viable_words->remove(try_password);
	
	//cout << "About to delete first viable words...\n";
	delete viable_words;
	//cout << "Deleted memory allocation errors. \n";
	viable_words = new_viable_words;
	//cout << "Set viable words to temp\n";

	
}

int Password::getNumberOfPasswordsLeft()
{
	int num_left = viable_words->size();
	return num_left;
}

void Password::displayViableWords()
{
	ListArrayIterator<String>* viable_pass_iterator = viable_words->iterator();
	
	while(viable_pass_iterator->hasNext())
	{
		(viable_pass_iterator->next())->displayString();
		cout << endl;
	}
	
	delete viable_pass_iterator;
}

String* Password::getOriginalWord(int index)
{
	String* word_from_original_list = all_words->get(index);
	return word_from_original_list;
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

int Password::getNumMatches(String* curr_word, String* word_guess)
{
	int counter = 0; 
	
	//is there any way to use a listarray iterator?
	
	for(int i = 0; i < len; i++)
	{
		if(curr_word->charAt(i) == word_guess->charAt(i))
		{
			counter++;
		}
	}
	
	return counter;
}