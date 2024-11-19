#ifndef TREE_H
#define TREE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define size_letters 27
#define max_size 100

typedef struct tree {
    char *value;
    struct tree *children[size_letters];
}*Tree;

/*
    It allocates memory for the tree.
*/

Tree createTree();

/*
    Insert a node in the tree on the right position.
*/

Tree insertNode(Tree root, char value);

/*
    This function insert a sufix in the tree.
*/

Tree insertSufix(Tree root, char *sufix);

/*
    This function build the tree.
*/

Tree build(FILE *input);

/*
    It combines 2 nodes into one.
*/

Tree combineTwoNodes(Tree root);

/*
    It compress the tree.
*/

Tree compress(Tree root);

/*
    It returns 1 if the tree is equal with NULL.
    Otherwise, it returns 0.
*/

int isTreeEmpty(Tree root);

/*
    It checks if the node is a leaf.
*/

int checkLeaf(Tree root);

/*
    It calculates the height of the tree.
*/

int height(Tree root);

/*
    It checks if the root has one node.
*/

int hasOneNode(Tree root);

/*
    It combine 2 strings.
*/

char *combineTwoStrings(char *str1, char *str2);

/*
    This function creates the suffixes.
*/

char **createSufixes(char *str);

/*
    It shows the value of each node from a certain level.
*/

void printLevel(Tree root, int level, FILE *output);

/*
    BFS for a tree
*/

void printTree(Tree root, FILE *output);

/*
    It reverse a string.
*/

void strrev(char *str);

/*
     This function deallocates the memory allocated for a tree. 
*/

void freeTree(Tree root);

#endif
