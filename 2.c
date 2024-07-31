#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main() {
    char input[100];

    // Prompt the user to enter a string
    printf("Enter a string: ");
    scanf("%s", input);

    // Check if the input string is a number
    int isDigit = 1; // Flag to check if all characters are digits
    for (int i = 0; i < strlen(input); i++) {
        if (!isdigit(input[i])) {
            isDigit = 0;
            break;
        }
    }

    if (isDigit) {
        printf("The input is a number: %s\n", input);
    } 
    else {
        printf("The input is not a number: %s\n", input);
    }

    return 0;
}