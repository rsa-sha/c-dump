#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int get_decimal(char a, char b){
	int nm = 0;
	if (a >= '0' && a <= '9'){
		nm = (a - '0') * 16;
	}
	else if (a >= 'A' && a <= 'F'){
		nm = (a - 'A' + 10) * 16;
	}
	else if (a >= 'a' && a <= 'f'){
		nm = (a - 'a' + 10) * 16;
	}
	if (b >= '0' && b <= '9'){
		nm += (b - '0');
	}
	else if (b >= 'A' && b <= 'F'){
		nm += (b - 'A' + 10);
	}
	else if (b >= 'a' && b <= 'f'){
		nm += (b - 'a' + 10);
	}
	return nm;
}

char *decimal_to_bin(int nm){
	char *bin = malloc(9);
	for(int i=0;i<8;i++){
		bin[i] = (nm & (1 << (7-i))) ? '1' : '0';
	}
	bin[8] = '\0';
	return bin;
}

char *hex_to_bin(char *hex_string){
	int len = strlen(hex_string);
	char *bin_str = (char*)malloc(len*4 + 1);
	for(int i=0;i<len;i+=2){
		int nm = get_decimal(hex_string[i], hex_string[i+1]);
		char *bin = decimal_to_bin(nm);
		strncat(bin_str, bin, 8);
	}
	return bin_str;
}
/*--------------------------------------------*/

int bin_to_decimal(char *base_str){
	int nm = 0;
	for(int i=0;i<6;i++){
		nm += (base_str[i] - '0') * (1 << (5-i));
	}
	return nm;
}

char decimal_to_base(int nm){
	if (nm >= 0 && nm <= 25){
		return nm + 'A';
	}
	else if (nm >= 26 && nm <= 51){
		return nm - 26 + 'a';
	}
	else if (nm >= 52 && nm <= 61){
		return nm - 52 + '0';
	}
	else if (nm == 62){
		return '+';
	}
	else if (nm == 63){
		return '/';
	}
	return '\0';
}

char *bin_to_base64(char *bin_str){
	// coverting group of 6 to decimal
	int len = strlen(bin_str);
	char *base64_str = (char*)malloc(len/6 + 1);
	for(int i=0;i<len;i+=6){
		char *group_of_6 = (char*)malloc(7);
		strncpy(group_of_6, bin_str+i, 6);
		int nm = bin_to_decimal(group_of_6);
		base64_str[i/6] = decimal_to_base(nm);
	}
	return base64_str;
}

/*--------------------------------------------*/

char *hex_to_base_64(char *hex_string){
	// convert hex string to binary
	char* bin_str = hex_to_bin(hex_string);
	// convert binary string to base64
	char* base_str = bin_to_base64(bin_str);
	return base_str;
}


int main(int argc, char **argv){
	if (argc != 2){
		printf("Usage: %s <hex_string>\n", argv[0]);
		return 1;
	}
	char *hex_string = argv[1];
	int hex_len = strlen(hex_string);
	if (hex_len % 2 != 0){
		printf("Hex string must have an even number of characters\n");
		return 1;
	}
	char *base64_string = hex_to_base_64(hex_string);
	printf("%s\n", base64_string);	
	return 0;
}
