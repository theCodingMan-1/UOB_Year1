#include <stdio.h>
#include <stdbool.h>

typedef struct node {
    struct node *left;
    int key;
    struct node *right;
} node;



// creates a root node without any left or right pointers.
node *newNode (int value) {
    node *p = malloc(sizeof(node));
    *p = (node) {NULL, value, NULL};
    return p;
}


// allows us to recursively go through the tree to insert an item,
// so that the tree remains sorted
node *insertSimple (node *p, int n) {
    if (p == NULL) p = newNode(n);
    else if (n < p->key) p->left = insertSimple(p->left, n);
    else if (n > p->key) p->right = insertSimple(p->right, n);
    return p;
}



// we provide this function with the address of the pointer to the current node
// so now the function can just update the pointer itself
bool insertNode(node **p, int n) {
    if (*p == NULL) {
        *p = newNode(n);
        return true;
    }

    else if (n < (*p)->key) return insertNode(&((*p)->left), n);
    else if (n > (*p)->key) return insertNode(&((*p)->right), n);
    else return false;

}



// below are functions used to wrap around the above functions.
// users do not have to interact with the pointer to pointer complexities.
// we have hidden these. 

typedef struct tree {
    node *root;
} tree;


tree *newTree() {
    tree *t = malloc(sizeof(tree));
    t->root = NULL;
    return t;
}

bool insert(tree *t, int n) {
    return insertNode(&(t->root), n);
}





void freeNodes(node *p) {
    if (p != NULL) {
        freeNodes(p->left);
        freeNodes(p->right);
        free(p);
    }
}

void freeTree(tree *t) {
    freeNodes(t->root);
    free(t);
}






node *findNode(node *p, int n) {
    if (p != NULL) {
        if (n < p->key) p = findNode(p->left, n);
        else if (n > p->key) p = findNode(p->right, n);
    }

    return p; // either returns the pointer to the value or NULL
}