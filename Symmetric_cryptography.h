#include "Symmetric_cryptography_core.h"

#ifdef __cplusplus

class Symmetric_cryptography
{

public:
    Symmetric_cryptography(const EVP_CIPHER *, char *, char *);
    int do_encrypt(char *input, int input_length, char *output);
    int do_decrypt(char *input, int input_length, char *output);
    
    void setkey(char *key)
    {
        this->key = key;
    }
    void setiv(char *iv)
    {
        this->iv = iv;
    };
    void setcipher(const EVP_CIPHER *);

private:
    const EVP_CIPHER *cipher;
    char *key, *iv;
};

Symmetric_cryptography::Symmetric_cryptography(const EVP_CIPHER *cipher, char *key, char *iv)
{
    this->cipher = cipher;
    this->iv = iv;
    this->key = key;
}

void Symmetric_cryptography::setcipher(const EVP_CIPHER *cipher)
{
    this->cipher = cipher;
}
int Symmetric_cryptography::do_encrypt(char *input, int input_length, char *output)
{
    return Encrypt_Data(cipher, key, iv, input, input_length, output);
}
int Symmetric_cryptography::do_decrypt(char *input, int input_length, char *output)
{
    return Decrypt_Data(cipher, key, iv, input, input_length, output);
}
#endif
