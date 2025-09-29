#include <stdio.h>

int main() {
    char encrypted_text[100];
    int frequency[26];
    int i, j;
    int max_freq = 0;
    int most_frequent_letter = 0;
    int key;
    char ch;

    for (i = 0; i < 26; i++) {
        frequency[i] = 0;
    }

    printf("Enter encrypted string: ");
    i = 0;
    while ((ch = getchar()) != '\n') {
        encrypted_text[i] = ch;
        i++;
    }
    encrypted_text[i] = '\0';

    for (i = 0; encrypted_text[i] != '\0'; i++) {
        ch = encrypted_text[i];
        if (ch >= 'A' && ch <= 'Z') {
            ch = ch - 'A' + 'a';
        }
        if (ch >= 'a' && ch <= 'z') {
            frequency[ch - 'a']++;
        }
    }

    for (i = 0; i < 26; i++) {
        if (frequency[i] > max_freq) {
            max_freq = frequency[i];
            most_frequent_letter = i;
        }
    }

    key = most_frequent_letter - 4;
    if (key < 0) {
        key = key + 26;
    }

    printf("Most frequent letter: %c\n", 'a' + most_frequent_letter);
    printf("Encryption key: %d\n", key);

    printf("Decrypted text: ");
    for (i = 0; encrypted_text[i] != '\0'; i++) {
        ch = encrypted_text[i];
        if (ch >= 'A' && ch <= 'Z') {
            ch = ch - 'A' + 'a';
        }
        if (ch >= 'a' && ch <= 'z') {
            ch = ch - key;
            if (ch < 'a') {
                ch = ch + 26;
            }
            printf("%c", ch);
        } else {
            printf("%c", encrypted_text[i]);
        }
    }
    printf("\n");

    return 0;
}