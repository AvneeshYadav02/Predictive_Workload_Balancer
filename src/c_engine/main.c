#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include "bst.h"
#include "resources.h"

#define COEFF_DISK_IO 10.0041
#define COEFF_HEAVY_COMP 50.0002
#define COEFF_OS_ROUT 3.0518
#define COEFF_USER_INTER 4.9865

#define SIM_SPEED 0.005

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
        new_task.task_id = atoi(token);
        
        token = strtok(NULL, ",");
        new_task.input_data = atoi(token);

        token = strtok(NULL, ",");
        new_task.priority = atoi(token);

        token = strtok(NULL, ",");
        new_task.execution_time = atoi(token);

        switch (new_task.task_id) {
            case 0:
                new_task.predicted_time = COEFF_OS_ROUT*(new_task.input_data);
                break;
            case 1:
                new_task.predicted_time = COEFF_USER_INTER*(new_task.input_data);
                break;
            case 2:
                new_task.predicted_time = COEFF_DISK_IO*(new_task.input_data);
                break;    
            case 3:
                new_task.predicted_time = COEFF_HEAVY_COMP*(new_task.input_data);
                break;
        }

        insert_task(new_task);
    }
    fclose(fp);
}

int main(){
    load_tasks("./data/incoming_tasks.csv");

    printf("Tasks Loaded\n------------------------STARTING EXECUTION------------------------\n\n");

    int task_no = 0;

    while(1){
        Task current_task = get_next();
        
        task_no++;

        if (current_task.process_id == -1){
            break;
        }

        int wait_time = (current_task.execution_time*1000) * SIM_SPEED;
        
        if (wait_time < 0){
            wait_time = 0;
        }

        printf("S.No - %d\nExecuting %s\nTask Priority: %d\nPredicted Execution Time: %.2fms\n", 
            task_no,
            current_task.task_name, 
            current_task.priority, 
            current_task.predicted_time);

        usleep(wait_time);

        printf("Time Taken: %.2fms\n\n", current_task.execution_time);
    }

    return 0;
}