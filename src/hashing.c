#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>

char* get_string_malloc(char input_string[]) {
    char * string;
    string = (char *) malloc(strlen(input_string));
    strcpy(string, input_string);
    return string;
}

char* hash(char to_hash[]) {
    // int length = sizeof(to_hash);

    unsigned char sha[SHA256_DIGEST_LENGTH];
    SHA256_CTX s;

    SHA256_Init(&s);
    SHA256_Update(&s, to_hash, strlen(to_hash));
    SHA256_Final(sha, &s);

    char string_out[SHA256_DIGEST_LENGTH*2+1];
    int n = strlen(to_hash);
    for (n = 0; n < SHA256_DIGEST_LENGTH; n++) {
        sprintf(&string_out[n*2], "%02x", sha[n]);
        }
    return get_string_malloc(string_out);
}

int count_zeros(char input_string[]){
    int length = strlen(input_string);
    int count = 0;
    for (int i=length-1; i >= 0; i--){
        if (input_string[i] != '0'){
            return count;
        }
        count++;
    }
    return count;
}
