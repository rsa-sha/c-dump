#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char *hex_to_bytes(char *hex_string){
    int len = strlen(hex_string);
    char *byte_str = (char*)malloc(len/2 + 1);
    for(int i=0;i<len;i+=2){
        char a = hex_string[i];
        char b = hex_string[i+1];
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
        byte_str[i/2] = nm;
    }
    byte_str[len/2] = '\0';
    return byte_str;
}

char *byte_to_hex(char byte){
    char *hex = (char*)malloc(3);
    sprintf(hex, "%02x", byte);
    return hex;
}

char *byte_str_to_hex(char *byte_str){
    int len = strlen(byte_str);
    char *hex_str = (char*)malloc(len*2 + 1);
    for(int i=0;i<len;i++){
        char *hex = byte_to_hex(byte_str[i]);
        strncat(hex_str, hex, 2);
    }
    return hex_str;
}


char *hex_str_xor(char *stra, char *strb){
       char *byte_str_a = hex_to_bytes(stra);
    char *byte_str_b = hex_to_bytes(strb);
    int len = strlen(byte_str_a);
    char *res = (char*)malloc(len+1);
    for(int i=0;i<len;i++){
        res[i] = byte_str_a[i] ^ byte_str_b[i];
    }
    res[len] = '\0';
    char *answer = byte_str_to_hex(res);
    return answer;
}



int main(int argc, char **argv){
	if (argc != 3){
		printf("Usage: %s <hex_string1> <hex_string2>\n", argv[0]);
		return 1;
	}
    char *stra = argv[1];
    char *strb = argv[2];
    int la = strlen(stra);
    int lb = strlen(strb);
    if(la%2!=0 || lb%2!=0){
        printf("Strings must have even number of characters\n");
        return 1;
    }
    if (la!=lb){
		printf("Strings must have equal number of characters\n");
		return 1;
	}
	char *xor_res = hex_str_xor(stra, strb);
    printf("%s\n", xor_res);	
	return 0;
}
