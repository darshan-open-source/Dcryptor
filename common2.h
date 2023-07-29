#ifndef COMMON2_H
#define COMMON2_H
#include<qstringlist.h>

QStringList algolist23 = {"AES","Aria","Blowfish","camellia","cast5","Des","triple des","idea","rc2","rc4","rc5","sm4"};
QStringList ciphermode3 = {"ecb","cbc","ofb","ocb"};
QStringList bits3 ={"128","192","256"};
QStringList aesmode3 = {"cbc","ccm","cfb1","cfb8","cfb","ctr","ecb","gcm","ocb","ofb","wrap","wrap_pad","xts"};
QStringList ariamode3={"cbc","ccm","cfb1","cfb8","cfb","ecb","gcm","ofb"};
QStringList bfmode_cast5_idea3 = {"cbc","cfb","ecb","ofb"};
QStringList cameliamode3 ={"cbc","ccm","cfb1","cfb8","cfb","ecb","gcm","ofb"};
QStringList desmode3 = {"cbc","cfb64","cfb1","cfb8","cfb","ecb"};
QStringList rc23 = {"cbc","40 cbc","64 cbc","cfb","cfb64","ecb","ofb"};
QStringList rc43 = {"rc4","rc4 40","rc4 hmac md5"};
QStringList rc53 = {"rc5_32_12_16_cbc","rc5_32_12_16_cfb","rc5_32_12_16_cfb64","rc5_32_12_16_ecb","rc5_32_12_16_ofb"};
QStringList sm43 = {"cbc","ctr","cfb","ecb","ofb"};

#include <openssl/evp.h>
#include<openssl/err.h>
#include <openssl/bio.h>
#include <string.h>
#include"filewidget.h"
#include<sys/stat.h>
int Base64_Encode2(char *input, int input_length, char *output)
{

    EVP_ENCODE_CTX *ctx = EVP_ENCODE_CTX_new();
    int output_len = 0, temp;
    EVP_EncodeInit(ctx);
    EVP_EncodeUpdate(ctx, (unsigned char *)output, &temp, (const unsigned char *)input, input_length);

    output_len += temp;
    EVP_EncodeFinal(ctx, (unsigned char *)output + output_len, &temp);
    output_len += temp;

    EVP_ENCODE_CTX_free(ctx);
    return output_len;
};
int Base64_Decode2(char *input, int input_length, char *output)
{

    EVP_ENCODE_CTX *ctx = EVP_ENCODE_CTX_new();
    int output_len = 0, temp;
    EVP_DecodeInit(ctx);
    EVP_DecodeUpdate(ctx, (unsigned char *)output, &temp, (const unsigned char *)input, input_length);

    output_len += temp;
    EVP_DecodeFinal(ctx, (unsigned char *)output + output_len, &temp);
    output_len += temp;

    EVP_ENCODE_CTX_free(ctx);
    return output_len;
};
typedef unsigned char *usc;




int Encrypt_File(const EVP_CIPHER *cipher, const char *key, const char *iv,const  char *filename,const  char *output_file,filewidget *f2)
{

    BIO *text_file = BIO_new_file(filename, "rb");
    BIO *encrypted_file = BIO_new_file(output_file, "wb");
    if (text_file == 0 || encrypted_file == 0)
    {
        qInfo("resolving");
   return 0;
   }
    struct stat st;
       stat(filename,&st);
    char plaintext[1024], encrypted_text[1024];
    size_t readded, enclen = 0;
    int  temp;
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    EVP_EncryptInit(ctx, cipher, (usc)key, iv == NULL ? 0 : (const usc)iv);


    while (BIO_read_ex(text_file, plaintext, 1024, &readded) == 1)
    {


        EVP_EncryptUpdate(ctx, (usc)encrypted_text, &temp, (usc)plaintext, readded);


        enclen += temp;
        QFileInfo f(filename);

        size_t x = (enclen*100)/f.size();
        f2->progress(x,0);


        BIO_write(encrypted_file, encrypted_text, temp);


    }
    char output[1024];
    int olen;

    EVP_EncryptFinal(ctx, (usc)output, &olen);
       f2->progress(100,0);

    BIO_write(encrypted_file, output, olen);
    BIO_flush(encrypted_file);
    BIO_free(text_file);
    BIO_free(encrypted_file);
    return 1;
};

int Decrypt_File(const EVP_CIPHER *cipher,const  char *key, const char *iv,const  char *filename,const  char *output_file,filewidget *f2)
{
    BIO *encryptedinput_file = BIO_new_file(filename, "rb");
    BIO *decrypted_file = BIO_new_file(output_file, "wb");\
    qInfo() << filename << "  "<<output_file;
    if (encryptedinput_file == 0 || decrypted_file == 0)
        return 0;
   qInfo() << "dddd";
    char plaintext[1024], encrypted_text[1024];
    size_t readded, enclen = 0;
    int temp;
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    EVP_DecryptInit(ctx, cipher, (usc)key, iv == NULL ? 0 : (const usc)iv);
    while (BIO_read_ex(encryptedinput_file, plaintext, 1024, &readded) == 1)
    {
        EVP_DecryptUpdate(ctx, (usc)encrypted_text, &temp, (usc)plaintext, readded);
        enclen += temp;
        QFileInfo f(filename);

        size_t x = (enclen*100)/f.size();
        f2->progress(x,0);;
        BIO_write(decrypted_file, encrypted_text, temp);
    }

    char output[1024];
    int olen;
    EVP_DecryptFinal(ctx, (usc)output, &olen);
       f2->progress(100,0);

    BIO_write(decrypted_file, output, olen);
    BIO_flush(decrypted_file);
    BIO_free(encryptedinput_file);
    BIO_free(decrypted_file);
    return 1;
};






#endif // COMMON2_H
