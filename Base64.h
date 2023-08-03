#ifndef BASE64_H
#define BASE64_H

#include <openssl/evp.h>

int Base64_Encode(char* input, int input_length, char* output);
int Base64_Decode(const char* input, int input_length, char* output);
#endif // BASE64_H
