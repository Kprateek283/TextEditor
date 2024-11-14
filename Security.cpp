#include "EditorWindow.h"
#include <cstdlib>  

char *base64_encode(const unsigned char *input, int length)
{
    BIO *bmem = NULL, *b64 = NULL;
    BUF_MEM *bptr = NULL;

    b64 = BIO_new(BIO_f_base64());
    bmem = BIO_new(BIO_s_mem());
    b64 = BIO_push(b64, bmem);
    BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);

    BIO_write(b64, input, length);
    BIO_flush(b64);
    BIO_get_mem_ptr(b64, &bptr);

    char *buff = (char *)malloc(bptr->length + 1);
    memcpy(buff, bptr->data, bptr->length);
    buff[bptr->length] = '\0';

    BIO_free_all(b64);

    return buff;
}

unsigned char *base64_decode(const char *input, int length, int *out_len)
{
    BIO *b64 = NULL, *bmem = NULL;
    unsigned char *buffer = (unsigned char *)malloc(length);
    memset(buffer, 0, length);

    b64 = BIO_new(BIO_f_base64());
    bmem = BIO_new_mem_buf((void *)input, length);
    bmem = BIO_push(b64, bmem);
    BIO_set_flags(bmem, BIO_FLAGS_BASE64_NO_NL);

    *out_len = BIO_read(bmem, buffer, length);

    BIO_free_all(bmem);

    return buffer;
}


void EditorWindow::encrypt_cb(Fl_Widget *w, void *data)
{
    clock_t start_time = clock();
    const char *plaintext = textbuf->text();
    const char *password = get_password();

    if (password == nullptr || password[0] == '\0')
    {
        fl_alert("Please provide a valid password to encrypt the file!");
        return;
    }

    int plaintext_len = strlen(plaintext);
    int ciphertext_len = plaintext_len + EVP_CIPHER_block_size(EVP_aes_128_cbc());

    unsigned char *ciphertext = (unsigned char *)malloc(ciphertext_len);
    unsigned char key[EVP_MAX_KEY_LENGTH], iv[EVP_MAX_IV_LENGTH];
    EVP_BytesToKey(EVP_aes_128_cbc(), EVP_sha256(), nullptr,
                   reinterpret_cast<const unsigned char *>(password),
                   strlen(password), 1, key, iv);

    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    EVP_EncryptInit_ex(ctx, EVP_aes_128_cbc(), nullptr, key, iv);

    int len;
    EVP_EncryptUpdate(ctx, ciphertext, &len, (unsigned char *)plaintext, plaintext_len);
    ciphertext_len = len;

    if (EVP_EncryptFinal_ex(ctx, ciphertext + len, &len) != 1)
    {
        fl_alert("Encryption finalization failed!");
        EVP_CIPHER_CTX_free(ctx);
        free(ciphertext);
        return;
    }
    ciphertext_len += len;

    EVP_CIPHER_CTX_free(ctx);

    char *encoded_ciphertext = base64_encode(ciphertext, ciphertext_len);
    textbuf->text(encoded_ciphertext);

    free(encoded_ciphertext);
    free(ciphertext);

    clock_t end_time = clock();
    std::cout << "Time taken to encrypt file: " << double(end_time - start_time) / CLOCKS_PER_SEC << " seconds" << std::endl;
}


void EditorWindow::decrypt_cb(Fl_Widget *w, void *data)
{
    clock_t start_time = clock();
    const char *encoded_ciphertext = textbuf->text(); 
    const char *password = get_password();

    if (password == nullptr || password[0] == '\0')
    {
        fl_alert("Please provide a valid password to decrypt the file!");
        return;
    }

    int encoded_len = strlen(encoded_ciphertext);
    int ciphertext_len;
    unsigned char *ciphertext = base64_decode(encoded_ciphertext, encoded_len, &ciphertext_len);

    unsigned char key[EVP_MAX_KEY_LENGTH], iv[EVP_MAX_IV_LENGTH];
    EVP_BytesToKey(EVP_aes_128_cbc(), EVP_sha256(), nullptr,
                   reinterpret_cast<const unsigned char *>(password),
                   strlen(password), 1, key, iv);

    unsigned char *decryptedtext = (unsigned char *)malloc(ciphertext_len + 1);  // Allocate memory for decrypted text
    EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
    EVP_DecryptInit_ex(ctx, EVP_aes_128_cbc(), nullptr, key, iv);

    int len;
    EVP_DecryptUpdate(ctx, decryptedtext, &len, ciphertext, ciphertext_len);
    int decryptedtext_len = len;

    if (EVP_DecryptFinal_ex(ctx, decryptedtext + len, &len) != 1)
    {
        fl_alert("Decryption finalization failed!");
        EVP_CIPHER_CTX_free(ctx);
        free(ciphertext);
        free(decryptedtext);
        return;
    }
    decryptedtext_len += len;

    EVP_CIPHER_CTX_free(ctx);

    decryptedtext[decryptedtext_len] = '\0';  
    textbuf->text((const char *)decryptedtext);

    free(ciphertext);
    free(decryptedtext);

    clock_t end_time = clock();
    std::cout << "Time taken to decrypt file: " << double(end_time - start_time) / CLOCKS_PER_SEC << " seconds" << std::endl;
}

const char *EditorWindow::get_password()
{
    return fl_input("Enter Password:", "");
}
