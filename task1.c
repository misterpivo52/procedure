#include <stdio.h>
#include <ctype.h>

int main() {
    int num_chars;
    int key;
    char ch;
    char encrypted_ch;
    int i;

    printf("Enter the number of characters to encrypt: ");
    scanf("%d", &num_chars);

    if (num_chars <= 0) {
        printf("Invalid number of characters\n");
        return 1;
    }

    printf("Enter encryption key [-128, 127]: ");
    scanf("%d", &key);

    if (key < -128 || key > 127) {
        printf("Invalid key range\n");
        return 1;
    }

    for (i = 1; i <= num_chars; i++) {
        printf("Enter character %d: ", i);
        scanf(" %c", &ch);

        if (!isalpha(ch)) {
            printf("Invalid input: must be a valid alphabetic character\n");
            i--;
            continue;
        }

        if (ch >= 'A' && ch <= 'Z') {
            ch = ch - 'A' + 'a';
        }

        encrypted_ch = ch + key;

        if (encrypted_ch > 'z') {
            encrypted_ch = encrypted_ch - 26;
        } else if (encrypted_ch < 'a') {
            encrypted_ch = encrypted_ch + 26;
        }

        printf("Encrypted character: %c\n", encrypted_ch);
    }

    return 0;
}