#include <stdio.h>
#include <ctype.h>
int modInverse(int a, int m);
void affineEncrypt(char text[], int a, int b);
void affineDecrypt(char text[], int a, int b);
int main() {
    char text[100];
    int a, b;
    printf("Enter the text: ");
    fgets(text, sizeof(text), stdin);
    printf("Enter the key values a and b: ");
    scanf("%d %d", &a, &b);
    affineEncrypt(text, a, b);
    printf("Encrypted text: %s\n", text);
    affineDecrypt(text, a, b);
    printf("Decrypted text: %s\n", text);
    return 0;
}
void affineEncrypt(char text[], int a, int b) {
    for (int i = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i])) {
            char offset = isupper(text[i]) ? 'A' : 'a';
            text[i] = ((a * (text[i] - offset) + b) % 26) + offset;
        }
    }
}
void affineDecrypt(char text[], int a, int b) {
    int a_inv = modInverse(a, 26); 
    for (int i = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i])) {
            char offset = isupper(text[i]) ? 'A' : 'a';
            text[i] = ((a_inv * (text[i] - offset - b + 26)) % 26) + offset;
        }
    }
}
int modInverse(int a, int m) {
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1)  
            return x;
    }
    return 1; 
}
