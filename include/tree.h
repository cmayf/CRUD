#ifndef TREE_H_
#define TREE_H_

#include "movie.h"

typedef struct Node {
    struct Movie* movie;
    char*          key;
    char         color;
    struct Node *left;
    struct Node *right;
    struct Node *parent;
} Node;

extern Node* Root;
extern Node* T_Nil;

extern char* possibleMatches[10];
extern int possibleMatchIndex;

/* Allocation/Deallocation */
Node* newNode();
void freeNode(Node* node);
void freeTree(Node* T);

/* Red-Black Tree Functions */
void rotateLeft( Node** T, Node* x);
void rotateRight(Node** T, Node* y);
void redBlackInsertFixup(Node** Root, Node* New);
void redBlackInsert(Node** T, struct Movie* movie);

/* Search Function */
Node* treeSearch(Node* root, char* key);
int isPossibleMatch(char* str1, char* str2);
void addPossibleMatch();
void freePossibleMatches();
char* getKeyword(char* str);

/* Utility Function */
char* lowercase(char* str);

#endif