#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 5

void prepareKey(char *key, char matrix[SIZE][SIZE]);
void removeDuplicates(char *key);
void fillMatrix(char *key, char matrix[SIZE][SIZE]);
void printMatrix(char matrix[SIZE][SIZE]);
void processText(char *text);
void encryptDigraph(char a, char b, char matrix[SIZE][SIZE], char *result);
void decryptDigraph(char a, char b, char matrix[SIZE][SIZE], char *result);
void playfairEncrypt(char *text, char *key, char *result);
void playfairDecrypt(char *text, char *key, char *result);

int main() {
    char key[100], text[100], result[100];
    
    printf("Enter the key: ");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = '\0'; // Remove newline character
    
    printf("Enter the plaintext: ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = '\0'; // Remove newline character

    char encrypted[100], decrypted[100];
    playfairEncrypt(text, key, encrypted);
    printf("Encrypted text: %s\n", encrypted);

    playfairDecrypt(encrypted, key, decrypted);
    printf("Decrypted text: %s\n", decrypted);

    return 0;
}

void prepareKey(char *key, char matrix[SIZE][SIZE]) {
    removeDuplicates(key);
    fillMatrix(key, matrix);
}

void removeDuplicates(char *key) {
    int len = strlen(key);
    char newKey[100];
    int index = 0;
    for (int i = 0; i < len; i++) {
        if (isalpha(key[i])) {
            key[i] = toupper(key[i]);
            int flag = 0;
            for (int j = 0; j < index; j++) {
                if (key[i] == newKey[j]) {
                    flag = 1;
                    break;
                }
            }
            if (!flag) {
                newKey[index++] = key[i];
            }
        }
    }
    newKey[index] = '\0';
    strcpy(key, newKey);
    strcat(key, "ABCDEFGHIKLMNOPQRSTUVWXYZ"); // Exclude J and add the rest
}

void fillMatrix(char *key, char matrix[SIZE][SIZE]) {
    int used[26] = {0};
    int row = 0, col = 0;

    for (int i = 0; key[i] != '\0'; i++) {
        char ch = key[i];
        if (!used[ch - 'A']) {
            matrix[row][col++] = ch;
            used[ch - 'A'] = 1;
            if (col == SIZE) {
                col = 0;
                row++;
            }
        }
    }
}

void printMatrix(char matrix[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%c ", matrix[i][j]);
        }
        printf("\n");
    }
}

void processText(char *text) {
    int len = strlen(text);
    for (int i = 0; i < len; i++) {
        text[i] = toupper(text[i]);
        if (text[i] == 'J') {
            text[i] = 'I';
        }
    }
    for (int i = 0; i < len - 1; i++) {
        if (text[i] == text[i + 1]) {
            memmove(&text[i + 2], &text[i + 1], len - i - 1);
            text[i + 1] = 'X';
            len++;
        }
    }
    if (len % 2 != 0) {
        text[len] = 'X';
        text[len + 1] = '\0';
    }
}

void encryptDigraph(char a, char b, char matrix[SIZE][SIZE], char *result) {
    int row1, col1, row2, col2;

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (matrix[i][j] == a) {
                row1 = i;
                col1 = j;
            }
            if (matrix[i][j] == b) {
                row2 = i;
                col2 = j;
            }
        }
    }

    if (row1 == row2) {
        result[0] = matrix[row1][(col1 + 1) % SIZE];
        result[1] = matrix[row2][(col2 + 1) % SIZE];
    } else if (col1 == col2) {
        result[0] = matrix[(row1 + 1) % SIZE][col1];
        result[1] = matrix[(row2 + 1) % SIZE][col2];
    } else {
        result[0] = matrix[row1][col2];
        result[1] = matrix[row2][col1];
    }
}

void decryptDigraph(char a, char b, char matrix[SIZE][SIZE], char *result) {
    int row1, col1, row2, col2;

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (matrix[i][j] == a) {
                row1 = i;
                col1 = j;
            }
            if (matrix[i][j] == b) {
                row2 = i;
                col2 = j;
            }
        }
    }

    if (row1 == row2) {
        result[0] = matrix[row1][(col1 + SIZE - 1) % SIZE];
        result[1] = matrix[row2][(col2 + SIZE - 1) % SIZE];
    } else if (col1 == col2) {
        result[0] = matrix[(row1 + SIZE - 1) % SIZE][col1];
        result[1] = matrix[(row2 + SIZE - 1) % SIZE][col2];
    } else {
        result[0] = matrix[row1][col2];
        result[1] = matrix[row2][col1];
    }
}

void playfairEncrypt(char *text, char *key, char *result) {
    char matrix[SIZE][SIZE];
    prepareKey(key, matrix);
    processText(text);

    int len = strlen(text);
    for (int i = 0; i < len; i += 2) {
        char enc[2];
        encryptDigraph(text[i], text[i + 1], matrix, enc);
        result[i] = enc[0];
        result[i + 1] = enc[1];
    }
    result[len] = '\0';
}

void playfairDecrypt(char *text, char *key, char *result) {
    char matrix[SIZE][SIZE];
    prepareKey(key, matrix);
    processText(text);

    int len = strlen(text);
    for (int i = 0; i < len; i += 2) {
        char dec[2];
        decryptDigraph(text[i], text[i + 1], matrix, dec);
        result[i] = dec[0];
        result[i + 1] = dec[1];
    }
    result[len] = '\0';
}
