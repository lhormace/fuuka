#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_TOKEN_LENGTH 100

enum token_types {
    TOK_KEYWORD,
    TOK_IDENTIFIER,
    TOK_OPERATOR,
    TOK_LITERAL,
};

struct token {
    enum token_types type;
    char value[MAX_TOKEN_LENGTH];
};

int is_operator(char c) {
    char operators[] = "+-*/=<>";
    return strchr(operators, c) != NULL;
}

int is_keyword(char *str) {
    char keywords[][MAX_TOKEN_LENGTH] = {"if", "else", "while", "for"};
    int i, num_keywords = sizeof(keywords) / sizeof(keywords[0]);

    for (i = 0; i < num_keywords; i++) {
        if (strcmp(str, keywords[i]) == 0) {
            return 1;
        }
    }

    return 0;
}

struct token get_next_token(char **input) {
    struct token tok;
    char *p = *input;

    // Skip whitespace
    while (isspace(*p)) {
        p++;
    }

    // Check for end of input
    if (*p == '\0') {
        tok.type = -1;
        return tok;
    }

    // Check for keyword or identifier
    if (isalpha(*p)) {
        int i = 0;
        while (isalnum(p[i]) || p[i] == '_') {
            i++;
        }
        strncpy(tok.value, p, i);
        tok.value[i] = '\0';
        *input += i;
        tok.type = is_keyword(tok.value) ? TOK_KEYWORD : TOK_IDENTIFIER;
        return tok;
    }

    // Check for operator
    if (is_operator(*p)) {
        strncpy(tok.value, p, 1);
        tok.value[1] = '\0';
        *input += 1;
        tok.type = TOK_OPERATOR;
        return tok;
    }

    // Check for literal
    if (isdigit(*p)) {
        int i = 0;
        while (isdigit(p[i])) {
            i++;
        }
        strncpy(tok.value, p, i);
        tok.value[i] = '\0';
        *input += i;
        tok.type = TOK_LITERAL;
        return tok;
    }

    // Invalid token
    tok.type = -1;
    return tok;
}

int main() {
    char input[] = "for (i = 0; i < 10; i++) { printf(\"%d\\n\", i); }";
    struct token tok;

    while ((tok = get_next_token(&input)).type != -1) {
        printf("%s\n", tok.value);
    }

    return 0;
}
