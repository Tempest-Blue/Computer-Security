/*******************************************************
 CSE127 Project
 User routines file
 
   Name: Kieth Vo 
   Email: tienvo52@gmail.com
   Student ID: A09632897

  You can change anything in this file, just make sure 
  that when you have found the password, you call 
  hack_system() function on it.

 CSE127 Example password guesser using memory protection

 *******************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/mman.h>
#include <string.h>
#include <unistd.h>
#include <setjmp.h>

// include our "system" header
#include "sysapp.h"

char * buffer;
char * page_start;
int page_size;

sigjmp_buf jumpout;


void handle_SEGV(int sig_num) {
	siglongjmp(jumpout, 1);
};

int demonstrate_signals() {
  	char *buf = page_start;

	// this call arranges that _if_ there is a SEGV fault in the future 
        // (anywhere in the program) then control will transfer directly to this
        // point with sigsetjmp returning 1
	if (sigsetjmp(jumpout, 1) == 1) 
		return 1; // we had a SEGV

	// 
	signal(SIGSEGV, SIG_DFL);
	signal(SIGSEGV, &handle_SEGV);

	// We will now cause a fault to happen
        *buf = 0;
	return 0;
}  

int main(int argc, char ** argv) {
	char guess[33];
	char c;
	int ok;
	int len;

	// get the physical page size
	page_size = sysconf(_SC_PAGESIZE);

	// allocate the buffer - we need at least 3 pages 
        // (because malloc doesn't give us page aligned data)
	//   Page:   1111111111111111222222222222222233333333333333334444444
	//           ^ buffer        ^page_start                    ^ end of buffer
        //   Prot:   ++++++++++++++++----------------+++++++++++++++++++++++
	//  
	buffer = (char*)malloc(3 * page_size);
	if (!buffer) {
		perror("malloc failed");
		exit(1);
	};
	// find the page start into buffer
	page_start = buffer + (page_size - ((unsigned long)buffer)%page_size);
	// fix the page start if there is not enough space 
	if ((page_start-buffer) <= 32)
		page_start += page_size;
	
	// prohibit access to the page
	if (mprotect(page_start, page_size, PROT_NONE) == -1) {
		perror("mprotect failed");
	};

	//
	// It is not strictly necessary to understand the previous code and
        // there will be no need to modify it.
        //
        // Here is a summary of the situation: page_start points to an address
        // that is unmapped (i.e., if you access the memory at *page_start it 
        // will cause a SEGV fault).  Moreover, the 32 characters _before_ 
        // page_start _are_ guaranteed to be allocated.  

        // Finally, this calls a sample function to demonstrate how you should
        // use signals to capture and continue from a faulting access
        // to protected memory.  You can remove this code after you understand it.
        // You will need to use signals in this manner to solve the assignment.
        
	/*if (demonstrate_signals(page_start) == 1) {
	  printf("We caught a page fault\n");
	}*/


	// set guess to zeros
	bzero(guess, sizeof(guess));

	// do the guessing (this is where your code goes)
        // we suggest a loop over the size of the possible 
        // password, each time trying all possible characters
        
	buffer = page_start - 1;	// Set buffer to the first byte before page_start
	int ascii = 33;			// Index for the ascii character
	int found = 0;			// # of characters found + Used as a guess index
	


	if (sigsetjmp(jumpout, 1) == 1) 
	{
		guess[found] = ascii;
		found++;
		buffer = page_start - (found + 1);
		memcpy(buffer, guess, found);
		buffer = page_start - 1;
		/*int temp;
		for (temp = 0; temp < 33; temp++)
		{
			if (guess[temp] != 0)
			{
				*buffer = guess[temp];
				buffer++;
			}
			else
			{
				break;
			}
		}*/
		
	}
	
	signal(SIGSEGV, SIG_DFL);
	signal(SIGSEGV, &handle_SEGV);

	for (ascii = 33; ascii < 127; ascii++)
	{
		*buffer = ascii;
		if (check_pass(buffer - found))
		{
			break;
		}
	}
	
	if (check_pass(guess)) {
	  printf("Password Found!\n");
	  hack_system(guess);
	};

	printf("Could not get the password!  Last guess was %s\n", guess);
	return 1;
};
