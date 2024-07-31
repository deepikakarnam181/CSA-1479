#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

// Token types
typedef enum {
    TOKEN_INT, TOKEN_PLUS, TOKEN_MINUS, TOKEN_MUL, TOKEN_DIV, TOKEN_LPAREN, TOKEN_RPAREN, TOKEN_EOF
} TokenType;

// Token structure
typedef struct {
    TokenType type;
    int value; // Only used for integer tokens
} Token;

Token tokens[256];
int tokenIndex = 0;
int currentToken = 0;

// Abstract Syntax Tree (AST) Nodes
typedef enum {
    AST_INT, AST_ADD, AST_SUB, AST_MUL, AST_DIV
} ASTNodeType;

typedef struct ASTNode {
    ASTNodeType type;
    int value; // Only used for integer nodes
    struct ASTNode *left;
    struct ASTNode *right;
} ASTNode;

// Function prototypes
void tokenize(const char *input);
Token getNextToken();
ASTNode *expr();
ASTNode *term();
ASTNode *factor();
void generateCode(ASTNode *node);

void tokenize(const char *input) {
    int i = 0;
    while (input[i] != '\0') {
        if (isdigit(input[i])) {
            tokens[tokenIndex].type = TOKEN_INT;
            tokens[tokenIndex].value = input[i] - '0';
            tokenIndex++;
        } else if (input[i] == '+') {
            tokens[tokenIndex++].type = TOKEN_PLUS;
        } else if (input[i] == '-') {
            tokens[tokenIndex++].type = TOKEN_MINUS;
        } else if (input[i] == '*') {
            tokens[tokenIndex++].type = TOKEN_MUL;
        } else if (input[i] == '/') {
            tokens[tokenIndex++].type = TOKEN_DIV;
        } else if (input[i] == '(') {
            tokens[tokenIndex++].type = TOKEN_LPAREN;
        } else if (input[i] == ')') {
            tokens[tokenIndex++].type = TOKEN_RPAREN;
        }
        i++;
    }
    tokens[tokenIndex].type = TOKEN_EOF;
}

Token getNextToken() {
    return tokens[currentToken++];
}

ASTNode *expr() {
    ASTNode *node = term();
    Token token = getNextToken();

    while (token.type == TOKEN_PLUS || token.type == TOKEN_MINUS) {
        ASTNode *newNode = malloc(sizeof(ASTNode));
        if (token.type == TOKEN_PLUS) {
            newNode->type = AST_ADD;
        } else {
            newNode->type = AST_SUB;
        }
        newNode->left = node;
        newNode->right = term();
        node = newNode;
        token = getNextToken();
    }
    currentToken--; // Put back the last token
    return node;
}

ASTNode *term() {
    ASTNode *node = factor();
    Token token = getNextToken();

    while (token.type == TOKEN_MUL || token.type == TOKEN_DIV) {
        ASTNode *newNode = malloc(sizeof(ASTNode));
        if (token.type == TOKEN_MUL) {
            newNode->type = AST_MUL;
        } else {
            newNode->type = AST_DIV;
        }
        newNode->left = node;
        newNode->right = factor();
        node = newNode;
        token = getNextToken();
    }
    currentToken--; // Put back the last token
    return node;
}

ASTNode *factor() {
    Token token = getNextToken();
    ASTNode *node = malloc(sizeof(ASTNode));

    if (token.type == TOKEN_INT) {
        node->type = AST_INT;
        node->value = token.value;
    } else if (token.type == TOKEN_LPAREN) {
        node = expr();
        getNextToken(); // Consume the closing parenthesis
    }
    return node;
}

void generateCode(ASTNode *node) {
    if (node->type == AST_INT) {
        printf("PUSH %d\n", node->value);
    } else
