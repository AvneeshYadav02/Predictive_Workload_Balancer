#ifndef RESOURCES_H
#define RESOURCES_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_LINE_LENGTH 1024

typedef struct{
    int process_id;
    int task_id;
    char task_name[32];
    int input_data;
    int priority;
    float execution_time;
    float predicted_time;
} Task;

void load_tasks(const char *filename);

#endif