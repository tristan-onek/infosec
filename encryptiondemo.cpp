#include <iostream>
#include <iomanip>
#include <cstring>
#include <openssl/evp.h>
#include <openssl/aes.h>

using namespace std;

// Function to print data in hexadecimal format
void printHex(const string& label, const unsigned char* data, size_t length) 
{
    cout << label << ": ";
    for (size_t i = 0; i < length; ++i) 
    {
        cout << hex << setw(2) << setfill('0') << static_cast<int>(data[i]);
    }
    cout << endl;
}

// AES Encryption function
void encryptAES(const unsigned char* plaintext, size_t plaintextLen,
                const unsigned char* key, const unsigned char* iv,
                unsigned char* ciphertext, int& ciphertextLen) 
{
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), nullptr, key, iv);

    int len;
    EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, plaintextLen);
    ciphertextLen = len;

    EVP_EncryptFinal_ex(ctx, ciphertext + len, &len);
    ciphertextLen += len;

    EVP_CIPHER_CTX_free(ctx);
}

// AES Decryption function
void decryptAES(const unsigned char* ciphertext, size_t ciphertextLen,
                const unsigned char* key, const unsigned char* iv,
                unsigned char* decryptedText, int& decryptedTextLen) 
{
    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), nullptr, key, iv);

    int len;
    EVP_DecryptUpdate(ctx, decryptedText, &len, ciphertext, ciphertextLen);
    decryptedTextLen = len;

    EVP_DecryptFinal_ex(ctx, decryptedText + len, &len);
    decryptedTextLen += len;

    EVP_CIPHER_CTX_free(ctx);
}

int main() 
{
    // Hardcoded key and IV
    unsigned char key[32] = "0123456789abcdef0123456789abcdef"; // 256-bit key
    unsigned char iv[16] = "abcdef0123456789";                  // 128-bit IV

    // Plaintext
    const char* plaintext = "This is a secret message.";
    size_t plaintextLen = strlen(plaintext);

    // Buffers for ciphertext and decrypted text
    unsigned char ciphertext[128];
    unsigned char decryptedText[128];
    int ciphertextLen = 0, decryptedTextLen = 0;

    // Encrypt the plaintext
    encryptAES(reinterpret_cast<const unsigned char*>(plaintext), plaintextLen, key, iv, ciphertext, ciphertextLen);
    printHex("Ciphertext", ciphertext, ciphertextLen);

    // Decrypt the ciphertext
    decryptAES(ciphertext, ciphertextLen, key, iv, decryptedText, decryptedTextLen);
    decryptedText[decryptedTextLen] = '\0'; // Null-terminate the decrypted string

    cout << "Decrypted Text: " << decryptedText << endl;

    return 0;
}
