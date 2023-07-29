#ifndef COMMON_H
#define COMMON_H
#include<qstringlist.h>
#ifndef __DEF
#define __DEF
QStringList algolist2 = {"AES","Aria","Blowfish","camellia","cast5","Des","triple des","idea","rc2","rc4","rc5","sm4"};
QStringList ciphermode = {"ecb","cbc","ofb","ocb"};
QStringList bits ={"128","192","256"};
QStringList aesmode = {"cbc","ccm","cfb1","cfb8","cfb","ctr","ecb","gcm","ocb","ofb","wrap","wrap_pad","xts"};
QStringList ariamode={"cbc","ccm","cfb1","cfb8","cfb","ecb","gcm","ofb"};
QStringList bfmode_cast5_idea = {"cbc","cfb","ecb","ofb"};
QStringList cameliamode ={"cbc","ccm","cfb1","cfb8","cfb","ecb","gcm","ofb"};
QStringList desmode = {"cbc","cfb64","cfb1","cfb8","cfb","ecb"};
QStringList rc2 = {"cbc","40 cbc","64 cbc","cfb","cfb64","ecb","ofb"};
QStringList rc4 = {"rc4","rc4 40","rc4 hmac md5"};
QStringList rc5 = {"rc5_32_12_16_cbc","rc5_32_12_16_cfb","rc5_32_12_16_cfb64","rc5_32_12_16_ecb","rc5_32_12_16_ofb"};
QStringList sm4 = {"cbc","ctr","cfb","ecb","ofb"};
#endif
#include <openssl/evp.h>
#include<openssl/err.h>
#include <openssl/bio.h>
#include <string.h>

#include"textwidget.h"
typedef unsigned char *usc;

int Encrypt_Data(const EVP_CIPHER *cipher, char *key, char *iv, char *input, int input_length, char *output,textwidget* t)
{
qInfo("encrypt called");
if(cipher != 0)qInfo("cipher not null");
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    int output_len = 0, temp;

   int a= EVP_EncryptInit(ctx, cipher, (const usc)key, iv == NULL ? 0 : (const usc)iv);

  int b=  EVP_EncryptUpdate(ctx, (usc)output, &temp, (const usc)input, input_length);
    output_len += temp;
     int x;
    x= (output_len*100)/input_length;
    t->progress(x);
   int c = EVP_EncryptFinal(ctx, (usc)output + output_len, &temp);
    output_len += temp;
     x= (output_len*100)/input_length;
    t->progress(x);
     t->progress(100);
qInfo()<<"df"<<ERR_error_string(ERR_get_error(),0)<<output_len;

    return output_len;
};
int Decrypt_Data(const EVP_CIPHER *cipher, char *key, char *iv, char *input, int input_length, char *output)
{

    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    int output_len = 0, temp;
    EVP_DecryptInit(ctx, cipher, (const usc)key, iv == NULL ? 0 : (const usc)iv);

    EVP_DecryptUpdate(ctx, (usc)output, &temp, (const usc)input, input_length);
    output_len += temp;
    EVP_DecryptFinal(ctx, (usc)output + output_len, &temp);
    output_len += temp;
    return output_len;
}

//int Encrypt_File(const EVP_CIPHER *cipher, char *key, char *iv, char *filename, char *output_file)
//{

//    BIO *text_file = BIO_new_file(filename, "r");
//    BIO *encrypted_file = BIO_new_file(output_file, "w");
//    if (text_file == 0 || encrypted_file == 0)
//        abort();
//    char plaintext[1024], encrypted_text[1024];
//    size_t readded, enclen = 0;
//    int temp;
//    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
//    EVP_EncryptInit(ctx, cipher, (usc)key, iv == NULL ? 0 : (const usc)iv);

//    while (BIO_read_ex(text_file, plaintext, 1024, &readded) == 1)
//    {

//        EVP_EncryptUpdate(ctx, (usc)encrypted_text, &temp, (usc)plaintext, readded);
//        enclen += temp;
//        BIO_write(encrypted_file, encrypted_text, temp);
//    }
//    char output[1024];
//    int olen;
//    EVP_EncryptFinal(ctx, (usc)output, &olen);

//    BIO_write(encrypted_file, output, olen);
//    BIO_free(text_file);
//    BIO_free(encrypted_file);
//    return 1;
//};

//int Decrypt_File(const EVP_CIPHER *cipher, char *key, char *iv, char *filename, char *output_file)
//{

//    BIO *encryptedinput_file = BIO_new_file(filename, "rb");
//    BIO *decrypted_file = BIO_new_file(output_file, "w");
//    if (encryptedinput_file == 0 || decrypted_file == 0)
//        abort();
//    char plaintext[1024], encrypted_text[1024];
//    size_t readded, enclen = 0;
//    int temp;
//    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
//    EVP_DecryptInit(ctx, cipher, (usc)key, iv == NULL ? 0 : (const usc)iv);
//printf("thre");
//    while (BIO_read_ex(encryptedinput_file, plaintext, 1024, &readded) == 1)
//    {

//        EVP_DecryptUpdate(ctx, (usc)encrypted_text, &temp, (usc)plaintext, readded);
//        enclen += temp;
//      int c =   BIO_write(decrypted_file, encrypted_text, temp);
//       printf("\n %d cccccccccc",c);
//    }
//    printf("readdedsc %d %s",readded,ERR_error_string(ERR_get_error(),0));
//    char output[1024];
//    int olen;
//    EVP_DecryptFinal(ctx, (usc)output, &olen);

//    BIO_write(decrypted_file, output, olen);
//    return 1;
//};
#endif // COMMON_H
