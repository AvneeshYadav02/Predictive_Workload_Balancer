#include "resources.h"
#include "bst.h"

Node* root = NULL;

// {insert_task} funciton: The function will insert a new task in the Binary 
// Search Tree as per its priority and execution time as predicted by the 
// model coefficients.
void insert_task(Task t){
    Node* new_node = (Node*)malloc(sizeof(Node)); 
    
    new_node -> task = t;
    new_node -> left = NULL;
    new_node -> right = NULL;

    // Condition to set the first node inserted as the 'root' node
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

// {get_next} function gets new tasks and omits them from the original BST
Task get_next(){
    //Empty Tree Case
    if (root == NULL){
        printf("\nTASKS FINISHED!\n");
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

// {inorder_traversal} recursively gets items in their increasing order of 
// execution priority and predicted time to execute.
void inorder_traversal(Node* node){    
    if (node == NULL){
        return;
    }

    inorder_traversal(node -> left);

    printf("|| %-5d | %-20s | %-10d | %-10d | %-10.2f ||\n", 
        node -> task.process_id, 
        node -> task.task_name, 
        node -> task.priority, 
        node -> task.input_data, 
        node -> task.predicted_time);

    inorder_traversal(node -> right);
}

// Prints the tree in a tabular structure.
void print_tree(){
    printf("SCHEDULED TASKS - SORTED BY PRIORITY AND TIME\n\n\n");
    printf("|| %-5s | %-20s | %-10s | %-10s | %-10s ||\n\n",
    "ID", "Task", "Priority", "Input(MB)", "Time(ms)");
    inorder_traversal(root); 
}