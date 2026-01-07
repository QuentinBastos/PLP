#ifndef LEXER_H
#define LEXER_H

typedef enum {
    TOKEN_NUMBER,
    TOKEN_OPERATOR,
    TOKEN_UNKNOWN,
    TOKEN_EOF
} TokenType;

typedef struct {
    TokenType type;
    char value[64];
} Token;

void skip_whitespace(const char** input);
Token get_number(const char** input);
Token get_operator(const char** input);

int tokenize(const char* input, Token* output);

#endif // LEXER_H