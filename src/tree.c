#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include "tree.h"

/* Movie Database */

#define RED   'R'
#define BLACK 'B'

// Red-Black Tree based on CLRS
// T_Nil is used as sentinal node
struct Node T_Nil_Node;
Node* T_Nil = &T_Nil_Node;

Node* Root = NULL;


// Allocates BST node
Node* newNode(struct Movie* movie)
{
    Node *retVal   = (Node*)malloc(sizeof(Node));
    retVal->movie  = create_movie();
    retVal->movie  = movie;
    retVal->key    = lowercase(movie->title);
    retVal->color  = RED;
    retVal->left   = NULL;
    retVal->right  = NULL;
    retVal->parent = NULL;

    return retVal;
}

void freeNode(Node* node)
{
    free_movie(node->movie);
    free(node->key);
    free(node);
}

void freeTree(Node* T)
{
    if (T->left != T_Nil)
        freeNode(T->left);
    if (T->right != T_Nil)
        freeNode(T->right);
}

void rotateLeft( Node** T, Node* x)
{
    Node *y  = x->right;    // set y
    x->right = y->left;     // turn y's left subtree into x's right subtree
    if (y->left != T_Nil) 
        y->left->parent = x;
    y->parent = x->parent;  // link x's parent to y
    if (x->parent == T_Nil) 
        *T = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;
    y->left   = x;            // put x on y's left
    x->parent = y;
}

void rotateRight(Node** T, Node* x)
{
    Node *y  = x->left;     // set y
    x->left  = y->right;    // turn y's right subtree into x's left subtree
    if (y->right != T_Nil) 
        y->right->parent = x;
    y->parent = x->parent;  // link x's parent to y
    if (x->parent == T_Nil) 
        *T = y;
    else if (x == x->parent->right)
        x->parent->right = y;
    else
        x->parent->left  = y;
    y->right  = x;         // put y on x's right
    x->parent = y;
}

void redBlackInsertFixup(Node** T, Node* z)
{
    Node* y = NULL;
    while (z->parent->color == RED)
    {
        if (z->parent == z->parent->parent->left)
        {
            y = z->parent->parent->right;
            if (y != T_Nil && y->color == RED)
            {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }
            else
            { 
                if (z == z->parent->right)
                    {
                        z = z->parent;
                        rotateLeft(T, z);
                    }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rotateRight(T, z->parent->parent);
            }
        }
        else if (z->parent == z->parent->parent->right)
        {
            y = z->parent->parent->left;
            if (y != T_Nil && y->color == RED)
            {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }
            else
            {
                if (z == z->parent->left)
                {
                    z = z->parent;
                    rotateRight(T, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                rotateLeft(T, z->parent->parent);
            }
        }
    }
    T[0]->color = BLACK;
}

void redBlackInsert(Node** T, struct Movie* movie)
{
    Node* z = newNode(movie);
    Node* y = T_Nil;
    Node* x = *T;

    // Find where to Insert node z into the binary search tree
    while (x != T_Nil) {
        y = x;
        if (strcmp(z->key, x->key) < 0) //(z->key < x->key)
            x = x->left;
        else
            x = x->right;
    }

    z->parent = y;
    if (y == T_Nil) 
        *T = z;
    else if (strcmp(z->key, y->key) < 0) //(z->key < y->key)
        y->left  = z;
    else
        y->right = z;
    
    // Init z as a red leaf
    z->left  = T_Nil;
    z->right = T_Nil;
    z->color = RED;

    // Ensure the Red-Black property is maintained
    redBlackInsertFixup(T, z);
}

char* possibleMatches[10];
int possibleMatchIndex = 0;

Node* treeSearch(Node* T, char* key)
{
    Node* curr = T;

    if(isPossibleMatch(key, curr->key) && possibleMatchIndex < 10)
        addPossibleMatch(curr);

    if(strcmp(key, curr->key) == 0)
    {
        freePossibleMatches();
        return curr;
    }
    else if(curr->left == T_Nil && curr->right == T_Nil)
        return T_Nil;
    
    
    if(strcmp(key, curr->key) < 0)
    {
        if(curr->left == T_Nil)
            return T_Nil;
        else
            return treeSearch(curr->left, key);
    }
    else
    {
        if(curr->right == T_Nil)
            return T_Nil;
        else
            return treeSearch(curr->right, key);
    }
    
}


/* Checks to see if two titles are possible matches */
int isPossibleMatch(char* str1, char* str2)
{
    char* keyword1 = getKeyword(str1);
    char* keyword2 = getKeyword(str2);
    if(strcmp(keyword1, keyword2) == 0 && strlen(keyword1) > 2)
    {
        free(keyword1);
        free(keyword2);
        return 1;
    }
    free(keyword1);
    free(keyword2);
    return 0;
}

void addPossibleMatch(Node* node)
{
    possibleMatches[possibleMatchIndex] = malloc(500);
    strcpy(possibleMatches[possibleMatchIndex], node->key);
    ++possibleMatchIndex;
}

void freePossibleMatches()
{
    for(int i = 0; i < possibleMatchIndex; ++i)
        free(possibleMatches[i]);
    possibleMatchIndex = 0;
}

/* Utility function to get the keyword of a title */
char* getKeyword(char* str)
{
    char* keyword = malloc(500);
    char* title = malloc(500);
    strcpy(title, str);
    char* token = strtok(title, " :");
    while(token != NULL)
    {
        if(strlen(keyword) < strlen(token))
        {
            strcpy(keyword, token);
        }
        token = strtok(NULL, " :");
    }
    free(title);
    return keyword;
}

/* Utility function to convert a string to lowercase
   so that bst searches are not case sensitive. */
char* lowercase(char* str)
{
    char* lowercaseStr = malloc(500);
    strcpy(lowercaseStr, str);
    for(int i = 0; lowercaseStr[i]; ++i)
        lowercaseStr[i] = tolower(lowercaseStr[i]);
    return lowercaseStr;
}