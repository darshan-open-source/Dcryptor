#pragma once

#include <openssl/evp.h>
#include<openssl/err.h>
#include <openssl/bio.h>
#include <string.h>

#include"textwidget.h"
#include"filewidget.h"
typedef unsigned char* usc;


int Encrypt_Data(const EVP_CIPHER* cipher, char* key, char* iv, char* input, int input_length, char* output, textwidget* t);
int Decrypt_Data(const EVP_CIPHER* cipher, char* key, char* iv, char* input, int input_length, char* output);

int Encrypt_File(const EVP_CIPHER* cipher, const char* key, const char* iv, const  char* filename, const  char* output_file, filewidget* f2);
int Decrypt_File(const EVP_CIPHER* cipher, const  char* key, const char* iv, const  char* filename, const  char* output_file, filewidget* f2);