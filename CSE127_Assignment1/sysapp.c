/*******************************************************
 CSE127 Project
 "system library" file
 
            DO NOT MODIFY THIS FILE!!

 *******************************************************/


#include <string.h>
#include <stdlib.h>
#include <stdio.h>


static char * correct_pass = "IsNotSecret";
int check_pass(char * pass) {
	int i,j,q;
	for (i=0; i<=strlen(correct_pass); i++) {
	  for (j=0;j<100;j++) {q=q+j;}  // artificial delay added for timehack
		if (pass[i] != correct_pass[i]) 
			return 0;
	}
	return 1;
};



void  hack_system(char * correct_pass) {
	if (check_pass(correct_pass)) {
		printf("OK: You have found correct password: '%s'\n", correct_pass);
		printf("OK: Congratulations!\n");
		exit(0);
	} else {
		printf("FAIL: The password '%s' is not correct! You have failed\n");
		exit(3);
	};
};

