#ifndef HASHING_H
#define HASHING_H

#include "../src/hashing.c"

char* get_string_malloc(char input_string[]);
char* hash(char to_hash[]);
int count_zeros(char input_string[]);

#endif /* HASHING_H */