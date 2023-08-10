#include "CryptoUtil.h"

int Encrypt_Data(const EVP_CIPHER* cipher, char* key, char* iv, char* input, int input_length, char* output, textwidget* t)
{
    qInfo("encrypt called");
    if (cipher != 0)qInfo("cipher not null");
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    int output_len = 0, temp;

    int a = EVP_EncryptInit(ctx, cipher, (const usc)key, iv == NULL ? 0 : (const usc)iv);

    int b = EVP_EncryptUpdate(ctx, (usc)output, &temp, (const usc)input, input_length);
    qInfo() << a << b;
    output_len += temp;
    int x;
    x = (output_len * 100) / input_length;
    t->progress(x);
    int c = EVP_EncryptFinal(ctx, (usc)output + output_len, &temp);
    output_len += temp;
    x = (output_len * 100) / input_length;
    t->progress(x);
    t->progress(100);
    qInfo() << "df" << c << ERR_error_string(ERR_get_error(), 0) << output_len;

    return output_len;
};
int Decrypt_Data(const EVP_CIPHER* cipher, char* key, char* iv, char* input, int input_length, char* output)
{

    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    int output_len = 0, temp;
    EVP_DecryptInit(ctx, cipher, (const usc)key, iv == NULL ? 0 : (const usc)iv);

    EVP_DecryptUpdate(ctx, (usc)output, &temp, (const usc)input, input_length);
    output_len += temp;
    EVP_DecryptFinal(ctx, (usc)output + output_len, &temp);
    output_len += temp;
    return output_len;
}






int Encrypt_File(const EVP_CIPHER* cipher, const char* key, const char* iv, const  char* filename, const  char* output_file, filewidget* f2)
{

    BIO* text_file = BIO_new_file(filename, "rb");
    BIO* encrypted_file = BIO_new_file(output_file, "wb");
    if (text_file == 0 || encrypted_file == 0)
    {
        qInfo("resolving");
        return 0;
    }
    
    char plaintext[1024], encrypted_text[1024];
    size_t readded, enclen = 0;
    int  temp;
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    EVP_EncryptInit(ctx, cipher, (usc)key, iv == NULL ? 0 : (const usc)iv);

    QFileInfo f(filename);

    while (BIO_read_ex(text_file, plaintext, 1024, &readded) == 1)
    {


        EVP_EncryptUpdate(ctx, (usc)encrypted_text, &temp, (usc)plaintext, readded);


        enclen += temp;

        size_t x = (enclen * 100) / f.size();
        f2->progress(x, 1);


        BIO_write(encrypted_file, encrypted_text, temp);


    }
    char output[1024];
    int olen;

    EVP_EncryptFinal(ctx, (usc)output, &olen);
    f2->progress(100, 1);

    BIO_write(encrypted_file, output, olen);
    BIO_flush(encrypted_file);
    BIO_free(text_file);
    BIO_free(encrypted_file);
    EVP_CIPHER_CTX_free(ctx);

    return 1;
};

int Decrypt_File(const EVP_CIPHER* cipher, const  char* key, const char* iv, const  char* filename, const  char* output_file, filewidget* f2)
{
    BIO* encryptedinput_file = BIO_new_file(filename, "rb");
    BIO* decrypted_file = BIO_new_file(output_file, "wb"); \
       
    if (encryptedinput_file == 0 || decrypted_file == 0)
        return 0;
    
    char plaintext[1024], encrypted_text[1024];
    size_t readded, enclen = 0;
    int temp;
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    QFileInfo f(filename);

    EVP_DecryptInit(ctx, cipher, (usc)key, iv == NULL ? 0 : (const usc)iv);
    while (BIO_read_ex(encryptedinput_file, plaintext, 1024, &readded) == 1)
    {
        EVP_DecryptUpdate(ctx, (usc)encrypted_text, &temp, (usc)plaintext, readded);
        enclen += temp;

        size_t x = (enclen * 100) / f.size();
        f2->progress(x, 0);;
        BIO_write(decrypted_file, encrypted_text, temp);
    }

    char output[1024];
    int olen;
    EVP_DecryptFinal(ctx, (usc)output, &olen);
    f2->progress(100, 0);

    BIO_write(decrypted_file, output, olen);
    BIO_flush(decrypted_file);
    BIO_free(encryptedinput_file);

    BIO_free(decrypted_file);
    EVP_CIPHER_CTX_free(ctx);

    return 1;
};


