#ifndef BST_H
#define BST_H

#include "resources.h"

typedef struct Node{
    Task task;
    struct Node* left;
    struct Node* right;
} Node;

extern Node* root;

void insert_task(Task t);
Task get_next();
void print_tree();

#endif