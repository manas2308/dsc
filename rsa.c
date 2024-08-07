#include <stdio.h>
#include <math.h>

// Function prototypes
long long int power(long long int base, long long int exponent, long long int modulus);
long long int gcd(long long int a, long long int b);
long long int modInverse(long long int a, long long int m);
long long int encrypt(long long int plaintext, long long int e, long long int n);
long long int decrypt(long long int ciphertext, long long int d, long long int n);

int main() {
    long long int p, q, n, phi, e, d;
    long long int plaintext, ciphertext;

    // Input two prime numbers
    printf("Enter two prime numbers p and q:\n");
    scanf("%lld %lld", &p, &q);

    // Compute n and phi
    n = p * q;
    phi = (p - 1) * (q - 1);

    // Choose e
    printf("Enter the value for e (1 < e < %lld and gcd(e, %lld) = 1):\n", phi, phi);
    scanf("%lld", &e);

    // Compute d
    d = modInverse(e, phi);

    if (d == -1) {
        printf("Invalid value for e.\n");
        return 1;
    }

    printf("Public key (e, n): (%lld, %lld)\n", e, n);
    printf("Private key (d, n): (%lld, %lld)\n", d, n);

    // Encryption
    printf("Enter plaintext (integer): ");
    scanf("%lld", &plaintext);
    ciphertext = encrypt(plaintext, e, n);
    printf("Encrypted ciphertext: %lld\n", ciphertext);

    // Decryption
    plaintext = decrypt(ciphertext, d, n);
    printf("Decrypted plaintext: %lld\n", plaintext);

    return 0;
}

// Function to perform modular exponentiation
long long int power(long long int base, long long int exponent, long long int modulus) {
    long long int result = 1;
    base = base % modulus;
    while (exponent > 0) {
        if (exponent % 2 == 1) {
            result = (result * base) % modulus;
        }
        exponent = exponent >> 1;
        base = (base * base) % modulus;
    }
    return result;
}

// Function to compute greatest common divisor
long long int gcd(long long int a, long long int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

// Function to compute modular inverse
long long int modInverse(long long int a, long long int m) {
    long long int m0 = m, t, q;
    long long int x0 = 0, x1 = 1;

    if (m == 1)
        return 0;

    while (a > 1) {
        q = a / m;
        t = m;

        m = a % m;
        a = t;

        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }

    if (x1 < 0)
        x1 += m0;

    return x1;
}

// Function to encrypt plaintext
long long int encrypt(long long int plaintext, long long int e, long long int n) {
    return power(plaintext, e, n);
}

// Function to decrypt ciphertext
long long int decrypt(long long int ciphertext, long long int d, long long int n) {
    return power(ciphertext, d, n);
}
