#include <stdio.h>
#include <ctype.h>
#include <string.h>

void encrypt(const char text[], const char key[], char encrypted_text[]);
void decrypt(const char text[], const char key[], char decrypted_text[]);

int main() {
    char text[100];
    char encrypted_text[100];
    char decrypted_text[100];
    const char *key = "QWERTYUIOPASDFGHJKLZXCVBNM";

    printf("Enter the text: ");
    fgets(text, sizeof(text), stdin);
     // Remove the newline character

    // Encrypt the text
    encrypt(text, key, encrypted_text);
    printf("Encrypted text: %s\n", encrypted_text);

    // Decrypt the text
    decrypt(encrypted_text, key, decrypted_text);
    printf("Decrypted text: %s\n", decrypted_text);

    return 0;
}

void encrypt(const char text[], const char key[], char encrypted_text[]) {
    for (int i = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i])) {
            char offset = isupper(text[i]) ? 'A' : 'a';
            encrypted_text[i] = key[toupper(text[i]) - 'A'];
            if (islower(text[i])) {
                encrypted_text[i] = tolower(encrypted_text[i]);
            }
        } else {
            encrypted_text[i] = text[i];
        }
    }
    encrypted_text[strlen(text)] = '\0';  // Ensure null-termination
}

void decrypt(const char text[], const char key[], char decrypted_text[]) {
    char reversekey[26];
    // Create a reverse key lookup
    for (int i = 0; i < 26; i++) {
        reversekey[key[i] - 'A'] = 'A' + i;
    }
    for (int i = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i])) {
            char offset = isupper(text[i]) ? 'A' : 'a';
            decrypted_text[i] = reversekey[toupper(text[i]) - 'A'];
            if (islower(text[i])) {
                decrypted_text[i] = tolower(decrypted_text[i]);
            }
        } else {
            decrypted_text[i] = text[i];
        }
    }
    decrypted_text[strlen(text)] = '\0';  // Ensure null-termination
}
