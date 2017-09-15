/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   AVLTree.h
 * Author: rainer
 *
 * Created on 26 de Agosto de 2017, 09:58
 */

#ifndef AVLTREE_H
#define AVLTREE_H

#include "Intranet.h"

struct Node;
struct Device* getDevice(Node* node);
int max(int a, int b);
int height(Node* node);
struct Node* newNode(struct Device* dev);
struct Node* rightRotate(Node* node);
struct Node* leftRotate(Node* node);
int balanceFactor(Node* node);
struct Node* insertNode(Node* node, struct Device* dev);
struct Node* deleteNode(struct Node* root, struct Device* key);
void preOrder(Node *root);
struct Node* AVLsearch(Node* root, int key);

#endif /* AVLTREE_H */

