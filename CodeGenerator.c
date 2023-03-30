#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"
#include "codegen.h"

void generate_code(struct ast_node *node) {
    switch (node->type) {
        case NODE_BINARY_OP:
            printf("(");
            generate_code(node->left);
            printf(" %s ", node->value);
            generate_code(node->right);
            printf(")");
            break;
        case NODE_IDENTIFIER:
            printf("%s", node->value);
            break;
        case NODE_LITERAL:
            printf("%s", node->value);
            break;
        default:
            fprintf(stderr, "Unknown node type: %d\n", node->type);
            exit(1);
    }
}

void generate_program(struct ast_node *node) {
    printf("#include <stdio.h>\n\n");
    printf("int main() {\n");
    printf("    printf(\"%%d\\n\", ");
    generate_code(node);
    printf(");\n");
    printf("    return 0;\n");
    printf("}\n");
}
 