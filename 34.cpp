#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_TOKENS 100
#define MAX_TOKEN_LENGTH 20

const char *determiners[] = {"the", "a"};
const char *nouns[] = {"dog", "cat"};
const char *verbs[] = {"chased", "caught"};

bool is_determiner(const char *word) {
    for (int i = 0; i < sizeof(determiners) / sizeof(determiners[0]); i++) {
        if (strcmp(word, determiners[i]) == 0) {
            return true;
        }
    }
    return false;
}

bool is_noun(const char *word) {
    for (int i = 0; i < sizeof(nouns) / sizeof(nouns[0]); i++) {
        if (strcmp(word, nouns[i]) == 0) {
            return true;
        }
    }
    return false;
}

bool is_verb(const char *word) {
    for (int i = 0; i < sizeof(verbs) / sizeof(verbs[0]); i++) {
        if (strcmp(word, verbs[i]) == 0) {
            return true;
        }
    }
    return false;
}

bool parse_sentence(char tokens[][MAX_TOKEN_LENGTH], int token_count) {
    // Simple grammar: S -> NP VP, NP -> DT NN, VP -> V NP
    // We expect tokens: DT NN V DT NN
    if (token_count != 5) {
        return false;
    }

    if (!is_determiner(tokens[0]) || !is_noun(tokens[1])) {
        return false;
    }

    if (!is_verb(tokens[2])) {
        return false;
    }

    if (!is_determiner(tokens[3]) || !is_noun(tokens[4])) {
        return false;
    }

    return true;
}

void tokenize(char *input, char tokens[][MAX_TOKEN_LENGTH], int *token_count) {
    char *token = strtok(input, " ");
    *token_count = 0;

    while (token != NULL) {
        strncpy(tokens[*token_count], token, MAX_TOKEN_LENGTH);
        (*token_count)++;
        token = strtok(NULL, " ");
    }
}

int main() {
    char input[MAX_TOKENS * MAX_TOKEN_LENGTH];
    char tokens[MAX_TOKENS][MAX_TOKEN_LENGTH];
    int token_count;

    printf("Enter a sentence: ");
    fgets(input, sizeof(input), stdin);

    // Remove newline character
    input[strcspn(input, "\n")] = 0;

    tokenize(input, tokens, &token_count);

    if (parse_sentence(tokens, token_count)) {
        printf("The sentence is grammatically correct.\n");
    } else {
        printf("The sentence is grammatically incorrect.\n");
    }

    return 0;
}
