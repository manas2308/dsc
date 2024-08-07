#include <stdio.h>
#include <string.h>
#include <stdlib.h>
void calculateFrequency(const char* text, double freq[26]) {
    int count[26] = {0};
    int total = 0;
    for (int i = 0; text[i] != '\0'; i++) {
        if (text[i] >= 'a' && text[i] <= 'z') {
            count[text[i] - 'a']++;
            total++;
        }
    }
    for (int i = 0; i < 26; i++) {
        freq[i] = (double)count[i] / total;
    }
}
void decrypt(const char* ciphertext, char* plaintext, int key) {
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (ciphertext[i] >= 'a' && ciphertext[i] <= 'z') {
            plaintext[i] = 'a' + (ciphertext[i] - 'a' - key + 26) % 26;
        } else {
            plaintext[i] = ciphertext[i];
        }
    }
    plaintext[strlen(ciphertext)] = '\0';
}
double chiSquared(const double observed[26], const double expected[26]) {
    double chi2 = 0.0;
    for (int i = 0; i < 26; i++) {
        double diff = observed[i] - expected[i];
        chi2 += (diff * diff) / expected[i];
    }
    return chi2;
}
void sortResults(int keys[], double chi2[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = i + 1; j < size; j++) {
            if (chi2[i] > chi2[j]) {
                double tempChi2 = chi2[i];
                chi2[i] = chi2[j];
                chi2[j] = tempChi2;

                int tempKey = keys[i];
                keys[i] = keys[j];
                keys[j] = tempKey;
            }
        }
    }
}
int main() {
    const char* ciphertext = "zpv mppl hsfbujoh upebz";
    char plaintext[100];
    double englishFreq[26] = {
        0.08167, 0.01492, 0.02782, 0.04253, 0.12702, 0.02228, 0.02015,
        0.06094, 0.06966, 0.00153, 0.00772, 0.04025, 0.02406, 0.06749,
        0.07507, 0.01929, 0.00095, 0.05987, 0.06327, 0.09056, 0.02758,
        0.00978, 0.02360, 0.00150, 0.01974, 0.00074
    };
    int keys[26];
    double chi2[26];
    int topN;
	printf("Enter the number of top possible plaintexts to display: ");
    scanf("%d", &topN);
	for (int key = 0; key < 26; key++) {
        decrypt(ciphertext, plaintext, key);
        double freq[26] = {0};
        calculateFrequency(plaintext, freq);
        chi2[key] = chiSquared(freq, englishFreq);
        keys[key] = key;
    }
	sortResults(keys, chi2, 26);
	printf("Top %d possible plaintexts:\n", topN);
    for (int i = 0; i < topN; i++) {
        decrypt(ciphertext, plaintext, keys[i]);
        printf("%2d: Key = %2d, Plaintext = %s\n", i + 1, keys[i], plaintext);
    }
    return 0;
}
