#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define MAX_LEN 100


char lowercase[] = "abcdefghijklmnopqrstuvwxyz";
char uppercase[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
char digits[]    = "0123456789";
char symbols[]   = "!@#$%^&*()_+-={}[]<>?/|";

void appendSet(char *dest, const char *src) {
    while (*src != '\0') {
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0';
}

void generatePassword(char *password, int length, const char *charSet) {
    int setLen = strlen(charSet);
    for (int i = 0; i < length; i++) {
        password[i] = charSet[rand() % setLen];
    }
    password[length] = '\0';
}


void getUserChoice(char *charSet) {
    char choice[10];

    printf("Character types to include:\n");
    printf("1 - Lowercase letters\n");
    printf("2 - Uppercase letters\n");
    printf("3 - Numbers\n");
    printf("4 - Symbols\n");
    printf("Enter choices (e.g., 1234 for all): ");
    scanf("%s", choice);

    *charSet = '\0';

    for (int i = 0; i < strlen(choice); i++) {
        switch (choice[i]) {
            case '1':
                appendSet(charSet + strlen(charSet), lowercase);
                break;
            case '2':
                appendSet(charSet + strlen(charSet), uppercase);
                break;
            case '3':
                appendSet(charSet + strlen(charSet), digits);
                break;
            case '4':
                appendSet(charSet + strlen(charSet), symbols);
                break;
            default:
                printf("Invalid option '%c' ignored.\n", choice[i]);
                break;
        }
    }
}


void checkPasswordStrength(const char *password) {
    int len = strlen(password);
    int hasLower = 0, hasUpper = 0, hasDigit = 0, hasSymbol = 0;

    for (int i = 0; i < len; i++) {
        if (islower(password[i])) hasLower = 1;
        else if (isupper(password[i])) hasUpper = 1;
        else if (isdigit(password[i])) hasDigit = 1;
        else hasSymbol = 1;
    }

    int score = hasLower + hasUpper + hasDigit + hasSymbol;

    printf("\nPassword Strength Check:\n");
    printf("- Length: %d\n", len);
    printf("- Contains: ");
    if (hasLower) printf("lowercase ");
    if (hasUpper) printf("uppercase ");
    if (hasDigit)  printf("digits ");
    if (hasSymbol) printf("symbols ");
    printf("\n");

    printf("- Strength: ");
    if (score == 4 && len >= 8)
        printf("Strong \n");
    else if (score >= 3 && len >= 5)
        printf("Medium \n");
    else
        printf("Weak ⚠\n");
}

int main() {
    char password[MAX_LEN];
    char charSet[200];
    int length;

    srand(time(NULL));

    printf("====================================\n");
    printf("    Random Password Generator \n");
    printf("====================================\n");

    getUserChoice(charSet);

    if (strlen(charSet) == 0) {
        printf("No valid character sets selected. Exiting...\n");
        return 1;
    }

    printf("Enter password length (max %d): ", MAX_LEN - 1);
    scanf("%d", &length);

    if (length <= 0 || length >= MAX_LEN) {
        printf("Invalid length. Try again.\n");
        return 1;
    }

    generatePassword(password, length, charSet);

    printf("\nGenerated Password: %s\n", password);
    checkPasswordStrength(password);

    printf("\nDone. Use it wisely and stay secure.\n");

 return 0;
}