#include <string.h>
#include <stdio.h>
#include <stdlib.h>


char *
man_find(char *arg){
	static char res[1024] = "";
	char val[64];
	for(int i=1; i<=9;i++){
		char final_cmd[128] = "man ";
		snprintf(val, sizeof(val), "%d", i);
		strcat(final_cmd, val);
		strcat(final_cmd, " ");
		strcat(final_cmd, arg);
		strcat(final_cmd, " > /dev/null 2>&1");
		if (system(final_cmd)==0){
			strcat(res, val);
			strcat(res, " ");
		}
	}
	return res;
}

int main(int argc, char **argv){
	// This tool will print out all the sections in which the given "string"
	// has an entry
	if(argc!=2){
		printf("Usage: %s argument\n", argv[0]);
		return EXIT_FAILURE;
	}
	char *res = man_find(argv[1]);
	if(strlen(res)==0){
		printf("No entry found for %s on any of the manual page\n", argv[1]);
		return EXIT_FAILURE;
	} else{
		printf("Entry for %s found on the following manual page(s) -> %s\n", argv[1], res);
	}
	return EXIT_SUCCESS;
}
