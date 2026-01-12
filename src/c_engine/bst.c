#include "resources.h"
#include "bst.h"

// insert_task funciton: The function will insert a new task in the Binary Search Tree as per its priority and execution time as predicted by the model coefficients.
void insert_task(Task t){
    Node* new_node = (Node*)malloc(sizeof(Node)); 
    
    new_node -> task = t;
    new_node -> left = NULL;
    new_node -> right = NULL;

    if (root == NULL){
        root = new_node;
        return;
    }

    Node* current = root;
    Node* parent = NULL;

    while (current != NULL){
        parent = current;

        if (new_node -> task.priority > current -> task.priority){
            current = current -> left;
        }else if(new_node -> task.priority < current -> task.priority){
            current = current -> right;
        }else {
            if (new_node -> task.predicted_time < current -> task.predicted_time){
                current = current -> left;
            }else {
                current = current -> right;
            }
        };
    }

    if (new_node -> task.priority > parent -> task.priority){
        parent -> left = new_node;
    }else if (new_node -> task.priority < parent -> task.priority){
        parent -> right = new_node;
    }else {
        if (new_node -> task.predicted_time < parent -> task.predicted_time){
            parent -> left = new_node;
        }else {
            parent -> right = new_node;
        }
    };
}

Task get_next(){
    //Empty Tree Case
    if (root == NULL){
        printf("EMPTY TREE!\nINSERT NEW TASKS!");
        Task empty_task = {0};
        empty_task.process_id = -1; 
        return empty_task;
    };

    Node* target;
    Task result;

    //Right Skewed Tree Case
    if(root -> left == NULL){
        target = root;
        root = root -> right;

        result = target -> task;
        free(target);
        return result;
    }

    Node* parent = root;

    while(parent->left != NULL && parent -> left -> left != NULL){
        parent = parent -> left;
    }

    target = parent -> left;

    //Re-assigning parent's left node to the next node in the tree (if any)
    parent -> left = target -> right;

    result = target -> task;

    //Freeing up the node
    free(target);

    return result;
}