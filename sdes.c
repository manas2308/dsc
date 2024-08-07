#include <stdio.h>
#include <stdint.h>
#include <string.h>
uint8_t sdesEncrypt(uint8_t plaintext, uint8_t key) {
    return (plaintext + key) % 256; 
}
uint8_t sdesDecrypt(uint8_t ciphertext, uint8_t key) {
    return (ciphertext - key + 256) % 256; 
}
void cbcEncrypt(uint8_t *plaintext, uint8_t *ciphertext, size_t length, uint8_t *key, uint8_t *iv) {
    uint8_t previousBlock[1];
    previousBlock[0] = iv[0];
    for (size_t i = 0; i < length; i++) {
        uint8_t inputBlock = plaintext[i] ^ previousBlock[0];
        ciphertext[i] = sdesEncrypt(inputBlock, key[0]);
        previousBlock[0] = ciphertext[i];
    }
}
void cbcDecrypt(uint8_t *ciphertext, uint8_t *plaintext, size_t length, uint8_t *key, uint8_t *iv) {
    uint8_t previousBlock[1];
    previousBlock[0] = iv[0];
    for (size_t i = 0; i < length; i++) {
        uint8_t decryptedBlock = sdesDecrypt(ciphertext[i], key[0]);
        plaintext[i] = decryptedBlock ^ previousBlock[0];
        previousBlock[0] = ciphertext[i];
    }
}
int main() {
    uint8_t iv = 0b10101010; // Binary initialization vector
    uint8_t key = 0b011111101; // Binary key
    uint8_t plaintext[4] = {0b00000001, 0b00100011, 0b00000000, 0b00000000}; // Example binary plaintext
    uint8_t expectedCiphertext[4] = {0b11110100, 0b00001011, 0b00000000, 0b00000000}; // Example binary ciphertext
    uint8_t ciphertext[4];
    uint8_t decryptedtext[4];
    cbcEncrypt(plaintext, ciphertext, sizeof(plaintext), &key, &iv);
    printf("Encrypted ciphertext: ");
    for (size_t i = 0; i < sizeof(ciphertext); i++) {
        printf("%02X ", ciphertext[i]);
    }
    printf("\n");
    cbcDecrypt(ciphertext, decryptedtext, sizeof(ciphertext), &key, &iv);
    printf("Decrypted plaintext: ");
    for (size_t i = 0; i < sizeof(decryptedtext); i++) {
        printf("%02X ", decryptedtext[i]);
    }
    printf("\n");
    return 0;
}
