#include <stdio.h>
#include <string.h>
#include <ctype.h>
void encrypt(char text[], char key[]);
void decrypt(char text[], char key[]);
void generateKey(char text[], char key[], char newKey[]);
int main() {
    char text[100], key[100];
    char newKey[100];
    printf("Enter the text: ");
    gets(text);
    printf("Enter the key: ");
    gets(key);
    generateKey(text, key, newKey);
    encrypt(text, newKey);
    printf("Encrypted text: %s\n", text);
    decrypt(text, newKey);
    printf("Decrypted text: %s\n", text);
    return 0;
}
void generateKey(char text[], char key[], char newKey[]) {
    int textLen = strlen(text);
    int keyLen = strlen(key);
    int i, j;
    for (i = 0, j = 0; i < textLen; i++, j++) {
        if (j == keyLen) j = 0;
        newKey[i] = toupper(key[j]);
    }
    newKey[i] = '\0';
}
void encrypt(char text[], char key[]) {
    int textLen = strlen(text);
    for (int i = 0; i < textLen; i++) {
        if (isalpha(text[i])) {
            char offset = isupper(text[i]) ? 'A' : 'a';
            text[i] = (toupper(text[i]) + key[i] - 2 * 'A') % 26 + offset;
        }
    }
}
void decrypt(char text[], char key[]) {
    int textLen = strlen(text);
    for (int i = 0; i < textLen; i++) {
        if (isalpha(text[i])) {
            char offset = isupper(text[i]) ? 'A' : 'a';
            text[i] = (toupper(text[i]) - key[i] + 26) % 26 + offset;
        }
    }
}
