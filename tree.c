#include "tree.h"

Tree createTree() {
    Tree root = malloc(sizeof(struct tree));
    if (root == NULL) {
        return NULL;
    }
    for (int i = 0; i < size_letters; i++) {
        root->children[i] = NULL;
    }
    root->value = NULL;
    return root;
}

int isTreeEmpty(Tree root) {
    if (root == NULL) {
        return 1;
    }
    return 0;
}

/*
    Functia insertNode insereaza un
    nou nod in arbore pe pozitia
    corespunzatoare 
*/
Tree insertNode(Tree root, char value) {
    if (isTreeEmpty(root) == 1) {
        return NULL;
    }
    int index = 0;
    if (value == '$') {
        index = 0;
    } else {
        index = value - 'a' + 1;
    }
    if (root->children[index] == NULL) {
        root->children[index] = createTree();
        root->children[index]->value = malloc(2 * sizeof(char));
        root->children[index]->value[0] = value;
        root->children[index]->value[1] = '\0';
    }
    return root;
}

int checkLeaf(Tree root) {
    for (int i = 0; i < size_letters; i++) {
        if (root->children[i] != NULL) {
            return 0;
        }
    }
    return 1;
}

int height(Tree root) {
    if (isTreeEmpty(root) == 1 || checkLeaf(root) == 1) {
        return 0;
    }
    int level = 0;
    for (int i = 0; i < size_letters; i++) {
        int tmp = height(root->children[i]);
        if (tmp > level) {
            level = tmp;
        }
    }
    return level + 1;
}

void printLevel(Tree root, int level, FILE *output) {
    if (isTreeEmpty(root) == 1) {
        return;
    }
    if (level == 0) {
        fprintf(output, "%s ", root->value);
        return;
    }
    for (int i = 0; i < size_letters; i++) {
        if (root->children[i] != NULL) {
            printLevel(root->children[i], level - 1, output);
        }
    }
}

void printTree(Tree root, FILE *output) {
    int len = height(root);
    for (int i = 1; i <= len; i++) {
        printLevel(root, i, output);
        fprintf(output, "\n");
    }
}

void strrev(char *str) {
    if (str == NULL) {
        return;
    }
    int len = strlen(str);
    for (int i = 0; i < len/2; i++) {
        char aux = str[i];
        str[i] = str[len - 1 - i];
        str[len - 1 - i] = aux;
    }
}

char **createSufixes(char *str) {
    if (str == NULL) {
        return NULL;
    }
    int len = strlen(str);
    char *new_str = malloc((len + 2) * sizeof(char));
    if (new_str == NULL) {
        return NULL;
    }
    strcpy(new_str, str);
    new_str[len] = '$';
    new_str[len + 1] = '\0';
    strrev(new_str);
    char **sufixes = malloc((len + 2) * sizeof(char *));
    if (sufixes == NULL) {
        free(new_str);
        return NULL;
    }
    for (int i = 0; i < len + 1; i++) {
        sufixes[i] = malloc((i + 2) * sizeof(char));
        strncpy(sufixes[i], new_str, (i + 1));
        sufixes[i][i + 1] = '\0';
        strrev(sufixes[i]);

    }
    free(new_str);
    return sufixes;
}

Tree insertSufix(Tree root, char *sufix) {
    if (isTreeEmpty(root) == 1) {
        return NULL;
    }
    Tree iter = root;
    for (int i = 0; i < strlen(sufix); i++) {
        int index;
        if (sufix[i] == '$') {
            index = 0;
        } else {
            index = sufix[i] - 'a' + 1;
        }
        if (iter->children[index] == NULL) {
            iter = insertNode(iter, sufix[i]);
        }
            iter = iter->children[index];
    }
    return root;
}

Tree build(FILE *input) {
    if (input == NULL) {
        return NULL;
    }
    Tree root = createTree();
    char buffer[max_size];
    int N = 0;
    fgets(buffer, max_size, input);
    N = atoi(buffer);
    for (int i = 0; i < N; i++) {
        fgets(buffer, max_size, input);
        buffer[strcspn(buffer, "\n")] = '\0';
        char **sufixes = createSufixes(buffer);
        for (int i = 0; i < strlen(buffer) + 1; i++) {
            root = insertSufix(root, sufixes[i]);
            free(sufixes[i]);
        }
        free(sufixes);
    }
    return root;
}

int hasOneNode(Tree root) {
    if (isTreeEmpty(root) == 1) {
        return 0;
    }
    int count = 0, index = 0;
    for (int i = 0; i < size_letters; i++) {
        if (root->children[i] != NULL) {
            count++;
            index = i;
        }
    }
    if (count == 1 && index != 0) {
        return 1;
    } else {
        return 0;
    }
}

char *combineTwoStrings(char *str1, char *str2) {
    int len1 = strlen(str1);
    int len2 = strlen(str2);
    char *result = (char *) malloc((len1 + len2 + 1) * sizeof(char));
    strcpy(result, str1);
    result = strcat(result, str2);
    result[len1 + len2] = '\0';
    return result;
}

Tree combineTwoNodes(Tree root) {
    if (isTreeEmpty(root) == 1) {
        return NULL;
    }
    if (hasOneNode(root) == 0) {
        return NULL;
    }
    int index = 0;
    for (int i = 0; i < size_letters; i++) {
        if (root->children[i] != NULL) {
            index = i;
        }
    }
    Tree tmp = root->children[index];
    char *result = combineTwoStrings(root->value, tmp->value);
    free(root->value);
    root->value = strdup(result);
    free(result);
    for (int i = 0; i < size_letters; i++) {
        root->children[i] = tmp->children[i];
    }
    free(tmp->value);
    free(tmp);
    return root;
}

Tree compress(Tree root) {
    if (isTreeEmpty(root) == 1) {
        return NULL;
    }
    if (checkLeaf(root) == 1) {
        return root;
    }
    for (int i = 0; i < size_letters; i++) {
        if (root->children[i] != NULL) {
            root->children[i] = compress(root->children[i]);
        }
    }
    for (int i = 0; i < size_letters; i++) {
        if (hasOneNode(root->children[i]) == 1) {
            root->children[i] = combineTwoNodes(root->children[i]);
        }
    }
    return root;
}

void freeTree(Tree root) {
    if (isTreeEmpty(root) == 1) {
        return;
    }
    for (int i = 0; i < size_letters; i++) {
        freeTree(root->children[i]);
    }
    if (root->value != NULL) {
        free(root->value);
    }
    free(root);
}
