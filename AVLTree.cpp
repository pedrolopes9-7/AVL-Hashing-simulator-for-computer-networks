/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "AVLTree.h"
#include "Intranet.h"
#include <string>
#include <iostream>

using namespace std;

struct Node {
    Device * key;
    Node *left;
    Node *right;
    int height;
};

struct Device* getDevice(Node* node) {
    if (node == NULL) return NULL;
    if (node != NULL) return node->key;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

int height(Node *n) {
    if (n == NULL)
            return 0;
    return n->height;
}

Node* newNode(struct Device* key) {
    Node * node = new Node;
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return(node);
}

Node * rightRotate(Node *y) {
    struct Node *x = y->left;
    struct Node *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

Node * leftRotate(Node *x) {
    struct Node *y = x->right;
    struct Node *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

int balanceFactor(Node *N) {
    if (N == NULL)
            return 0;
    return height(N->left) - height(N->right);
}

Node* insertNode(Node* node, struct Device* key) {
    if (node == NULL)
            return(newNode(key));

    if (returnIP(key) < returnIP((struct Device*)node->key))
            node->left = insertNode(node->left, key);
    else if (returnIP(key) > returnIP((struct Device*)node->key))
            node->right = insertNode(node->right, key);
    else
            return node;

    node->height = 1 + max(height(node->left),
            height(node->right));

    int balance = balanceFactor(node);

    if (balance > 1 && returnIP(key) < returnIP(node->left->key))
            return rightRotate(node);

    if (balance < -1 && returnIP(key) > returnIP(node->right->key))
            return leftRotate(node);

    if (balance > 1 && returnIP(key) > returnIP(node->left->key)) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
    }

    if (balance < -1 && returnIP(key) < returnIP(node->right->key)) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
    }

    return node;
}

void preOrder(Node *root) {
    if (root != NULL) {
            printDevice(root->key);
            cout << endl;
            preOrder(root->left);
            preOrder(root->right);
    }
}

Node* AVLsearch(Node* root, int key) {
    if (root == NULL || returnIP(root->key) == key)
            return root;

    if (returnIP(root->key) < key)
            return AVLsearch(root->right, key);

    return AVLsearch(root->left, key);
}

struct Node * minValueNode(struct Node* node) {
    struct Node* current = node;

    while (current->left != NULL)
            current = current->left;

    return current;
}

struct Node* deleteNode(struct Node* root, struct Device* key) {

    if (root == NULL)
            return root;

    if (returnIP(key) < returnIP((Device*)root->key))
            root->left = deleteNode(root->left, key);

    else if (returnIP(key) > returnIP((Device*)(root->key)))
            root->right = deleteNode(root->right, key);

    else {
        if ((root->left == NULL) || (root->right == NULL)) {
                struct Node *temp = root->left ? root->left :
                        root->right;

                if (temp == NULL) {
                        temp = root;
                        root = NULL;
                }
                else *root = *temp;
                delete(temp);
        }
        else {
                struct Node* temp = minValueNode(root->right);

                root->key = temp->key;
                root->right = deleteNode(root->right, temp->key);
        }
    }

    if (root == NULL)
            return root;

    root->height = 1 + max(height(root->left),
            height(root->right));

    int balance = balanceFactor(root);

    if (balance > 1 && balanceFactor(root->left) >= 0)
            return rightRotate(root);

    if (balance > 1 && balanceFactor(root->left) < 0) {
            root->left = leftRotate(root->left);
            return rightRotate(root);
    }

    if (balance < -1 && balanceFactor(root->right) <= 0)
            return leftRotate(root);

    if (balance < -1 && balanceFactor(root->right) > 0) {
            root->right = rightRotate(root->right);
            return leftRotate(root);
    }
    return root;
}