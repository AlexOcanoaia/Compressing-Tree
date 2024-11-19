#include "tree.h"

int main(int argc, char *argv[]) {
    FILE *input = fopen(argv[argc - 2], "rt");
    if (input == NULL) {
        return -1;
    }
    FILE *output = fopen(argv[argc - 1], "wt");
    if (output == NULL) {
        return -1;
    }
    Tree root = build(input);
    root = compress(root);
    printTree(root, output);
    freeTree(root);
    fclose(input);
    fclose(output);
}