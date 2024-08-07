#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MATRIX_SIZE 2

void printMatrix(int matrix[MATRIX_SIZE][MATRIX_SIZE]);
void encrypt(char *plaintext, int keyMatrix[MATRIX_SIZE][MATRIX_SIZE], char *ciphertext);
void decrypt(char *ciphertext, int keyMatrix[MATRIX_SIZE][MATRIX_SIZE], char *plaintext);
int mod(int a, int m);
int modInverse(int a, int m);
void matrixMultiply(int mat1[MATRIX_SIZE][MATRIX_SIZE], int mat2[MATRIX_SIZE][MATRIX_SIZE], int result[MATRIX_SIZE][MATRIX_SIZE]);
void matrixTranspose(int mat[MATRIX_SIZE][MATRIX_SIZE], int result[MATRIX_SIZE][MATRIX_SIZE]);

int main() {
    int keyMatrix[MATRIX_SIZE][MATRIX_SIZE] = {{0}};
    char plaintext[100], ciphertext[100], decryptedText[100];

    printf("Enter the 2x2 key matrix (4 numbers): ");
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            scanf("%d", &keyMatrix[i][j]);
        }
    }

    printf("Enter the plaintext (length should be multiple of 2): ");
    scanf("%s", plaintext);

    encrypt(plaintext, keyMatrix, ciphertext);
    printf("Encrypted text: %s\n", ciphertext);

    decrypt(ciphertext, keyMatrix, decryptedText);
    printf("Decrypted text: %s\n", decryptedText);

    return 0;
}

void printMatrix(int matrix[MATRIX_SIZE][MATRIX_SIZE]) {
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

void encrypt(char *plaintext, int keyMatrix[MATRIX_SIZE][MATRIX_SIZE], char *ciphertext) {
    int length = strlen(plaintext);
    if (length % 2 != 0) {
        printf("Plaintext length should be multiple of 2.\n");
        exit(1);
    }

    int ptMatrix[MATRIX_SIZE][MATRIX_SIZE];
    int ctMatrix[MATRIX_SIZE][MATRIX_SIZE];

    for (int i = 0; i < length; i += 2) {
        ptMatrix[0][0] = plaintext[i] - 'A';
        ptMatrix[0][1] = plaintext[i + 1] - 'A';

        matrixMultiply(keyMatrix, ptMatrix, ctMatrix);

        ciphertext[i] = ctMatrix[0][0] % 26 + 'A';
        ciphertext[i + 1] = ctMatrix[0][1] % 26 + 'A';
    }
    ciphertext[length] = '\0';
}

void decrypt(char *ciphertext, int keyMatrix[MATRIX_SIZE][MATRIX_SIZE], char *plaintext) {
    int length = strlen(ciphertext);
    if (length % 2 != 0) {
        printf("Ciphertext length should be multiple of 2.\n");
        exit(1);
    }

    int keyInverse[MATRIX_SIZE][MATRIX_SIZE];
    int ctMatrix[MATRIX_SIZE][MATRIX_SIZE];
    int ptMatrix[MATRIX_SIZE][MATRIX_SIZE];

    matrixInverse(keyMatrix, keyInverse);

    for (int i = 0; i < length; i += 2) {
        ctMatrix[0][0] = ciphertext[i] - 'A';
        ctMatrix[0][1] = ciphertext[i + 1] - 'A';

        matrixMultiply(keyInverse, ctMatrix, ptMatrix);

        plaintext[i] = ptMatrix[0][0] % 26 + 'A';
        plaintext[i + 1] = ptMatrix[0][1] % 26 + 'A';
    }
    plaintext[length] = '\0';
}

void matrixMultiply(int mat1[MATRIX_SIZE][MATRIX_SIZE], int mat2[MATRIX_SIZE][MATRIX_SIZE], int result[MATRIX_SIZE][MATRIX_SIZE]) {
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            result[i][j] = 0;
            for (int k = 0; k < MATRIX_SIZE; k++) {
                result[i][j] += mat1[i][k] * mat2[k][j];
            }
            result[i][j] = mod(result[i][j], 26);
        }
    }
}

void matrixTranspose(int mat[MATRIX_SIZE][MATRIX_SIZE], int result[MATRIX_SIZE][MATRIX_SIZE]) {
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            result[i][j] = mat[j][i];
        }
    }
}

int mod(int a, int m) {
    return (a % m + m) % m;
}

int modInverse(int a, int m) {
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return -1; // No modular inverse if no solution
}

void matrixInverse(int mat[MATRIX_SIZE][MATRIX_SIZE], int result[MATRIX_SIZE][MATRIX_SIZE]) {
    int determinant = (mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0]) % 26;
    determinant = mod(determinant, 26);
    int detInv = modInverse(determinant, 26);

    if (detInv == -1) {
        printf("Matrix is not invertible.\n");
        exit(1);
    }

    int adjMatrix[MATRIX_SIZE][MATRIX_SIZE] = {
        {mat[1][1], -mat[0][1]},
        {-mat[1][0], mat[0][0]}
    };

    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            result[i][j] = mod(adjMatrix[i][j] * detInv, 26);
        }
    }
}
