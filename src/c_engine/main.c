#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "bst.h"
#include "resources.h"

#define COEFF 49.5817
#define INTERCEPT -10590.7672

void load_tasks(const char* filename){
    FILE *fp;
    fp = fopen(filename, "r");
    if (fp == NULL){
        printf("FILE DOESN'T EXIST :()");
        exit(1);
        }
 
    char line[MAX_LINE_LENGTH];

    //Reading the header once and throwing it away since it contains just the title
    fgets(line, MAX_LINE_LENGTH, fp);

    while(fgets(line, MAX_LINE_LENGTH, fp)){
        Task new_task;

        char* token = strtok(line, ",");
        new_task.process_id = atoi(token);

        token = strtok(NULL, ",");
        strcpy(new_task.task_name, token);
        
        token = strtok(NULL, ",");
        
        token = strtok(NULL, ",");
        new_task.input_data = atoi(token);

        token = strtok(NULL, ",");
        new_task.priority = atoi(token);

        token = strtok(NULL, ",");
        new_task.execution_time = atoi(token);

        new_task.predicted_time = COEFF*(new_task.input_data) + INTERCEPT;

        insert_task(new_task);
    }
    fclose(fp);
}

int main(){
    load_tasks("./data/incoming_tasks.csv");

    printf("Tasks Loaded:\n");
    print_tree();

    return 0;
}