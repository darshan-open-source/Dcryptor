#ifndef BASE64_H
#define BASE64_H

#include <openssl/evp.h>

int Base64_Encode(char *input, int input_length, char *output)
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
int Base64_Decode(const char *input, int input_length, char *output)
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
#endif // BASE64_H
