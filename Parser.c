struct ast_node *parse_expression(char **input, int precedence) {
    struct ast_node *left = parse_primary(input);

    while (1) {
        struct token tok = get_next_token(input);

        if (tok.type != TOK_OPERATOR || tok.precedence < precedence) {
            *input -= strlen(tok.value);
            break;
        }

        struct ast_node *right = parse_expression(input, tok.precedence + 1);

        struct ast_node *node = malloc(sizeof(struct ast_node));
        node->type = NODE_BINARY_OP;
        strncpy(node->value, tok.value, MAX_TOKEN_LENGTH);
        node->left = left;
        node->right = right;
        node->precedence
        left = node;
    }

    return left;
}

struct ast_node *parse_primary(char **input) {
    struct token tok = get_next_token(input);
	if (tok.type == TOK_IDENTIFIER) {
	    struct ast_node *node = malloc(sizeof(struct ast_node));
	    node->type = NODE_IDENTIFIER;
	    strncpy(node->value, tok.value, MAX_TOKEN_LENGTH);
	    node->left = NULL;
	    node->right = NULL;
	    node->precedence = 0;
	    return node;
	}

	if (tok.type == TOK_LITERAL) {
	    struct ast_node *node = malloc(sizeof(struct ast_node));
	    node->type = NODE_LITERAL;
	    strncpy(node->value, tok.value, MAX_TOKEN_LENGTH);
	    node->left = NULL;
	    node->right = NULL;
	    node->precedence = 0;
	    return node;
	}

	if (tok.type == TOK_OPERATOR && strcmp(tok.value, "(") == 0) {
	    struct ast_node *expr = parse_expression(input, 0);
	    tok = get_next_token(input);
	    if (tok.type != TOK_OPERATOR || strcmp(tok.value, ")") != 0) {
	        fprintf(stderr, "Expected ')' but got '%s'\n", tok.value);
	        exit(1);
	    }
	    return expr;
	}

	fprintf(stderr, "Unknown token '%s'\n", tok.value);
	exit(1);
}

struct ast_node *parse(char *input) {
	char *p = input;
	return parse_expression(&p, 0);
}
