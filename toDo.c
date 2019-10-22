/*
 * CS 261 Assignment 4
 * Name: 
 * Date: 
 */

#include "dynamicArray.h"
#include "task.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/**
 * Loads into heap a list from a file with lines formatted like
 * "priority, name".
 * @param heap
 * @param file
 */
void listLoad(DynamicArray* heap, FILE* file)
{
    const int FORMAT_LENGTH = 256;
    char format[256];
    snprintf(format, FORMAT_LENGTH, "%%d, %%%d[^\n]", TASK_NAME_SIZE);
    
    Task temp;
    while (fscanf(file, format, &temp.priority, &temp.name) == 2)
    {
        dyHeapAdd(heap, taskNew(temp.priority, temp.name), taskCompare);
    }
}

/**
 * Writes to a file all tasks in heap with lines formatted like
 * "priority, name".
 * @param heap
 * @param file
 */
void listSave(DynamicArray* heap, FILE* file)
{
    for (int i = 0; i < dySize(heap); i++)
    {
        Task* task = dyGet(heap, i);
        fprintf(file, "%d, %s\n", task->priority, task->name);
    }
}

/**
 * Prints every task in heap.
 * @param heap
 */
void listPrint(DynamicArray* heap)
{
    DynamicArray* temp = dyNew(1);
    dyCopy(heap, temp);
    while (dySize(temp) > 0)
    {
        Task* task = dyHeapGetMin(temp);
        printf("\n");
        taskPrint(task);
        printf("\n");
        dyHeapRemoveMin(temp, taskCompare);
    }
    dyDelete(temp);
}

/**
 * Handles the given command.
 * @param list
 * @param command
 */
void handleCommand(DynamicArray* list, char command)
{
    // FIXME: Implement
    //FILE *in; 
    char inFile[100];
    switch(command)
    {
        case 'l':


            printf("You have chosen to load a file!\n");
            //FILE *in; 
           // char inFile[100];
            puts("Enter the file name to read in. ");
            fgets(inFile, 100, stdin);

            if(inFile[strlen(inFile)-1] == '\n')
            {
                inFile[strlen(inFile)-1] = '\0';
            }

            FILE *in; 
            in = fopen(inFile, "r");

            if (in != NULL)
            {
               // printf("Before file load\n"); testing
                listLoad(list, in);
                printf("file loaded correctly\n");
            
                fclose(in);
                printf("file closed\n");
            }
            else
            {
                printf("File failed to load...\n");
            }
            //printf("testing...\n");

           // listPrint(list); testing

            break;

        case 's':
            printf("You have chosen to save a file!\n");
            //FILE *in; 
           // char inFile[100];
            puts("Enter the file name to create in. ");
            fgets(inFile, 100, stdin);

            if(inFile[strlen(inFile)-1] == '\n')
            {
                inFile[strlen(inFile)-1] = '\0';
            }

            FILE *save; 
            save = fopen(inFile, "w+");

            if (save != NULL)
            {
               // printf("Before file load\n"); testing
                listSave(list, save);
                printf("file saved correctly\n");
            
                fclose(save);
                printf("file closed\n");
            }
            else
            {
                printf("File failed to load...\n");
            }
            break;

        case 'a':
            printf("You have chosen to add a new task!\n");

            int priority = 0;
            char taskName[TASK_NAME_SIZE];

            printf("Enter the task name\n");
            fgets(taskName, TASK_NAME_SIZE, stdin);

            if(taskName[strlen(taskName)-1] == '\n')
            {
                taskName[strlen(taskName)-1] = '\0';
            }
            //simple input validation
            do  {
                printf("Now enter the priority (0 being the highest priority, 999 being lowest\n");
                scanf("%d", &priority);
            } while (priority <= 0 && priority >= 999);

            //clear trailing newline
            while (getchar() != '\n');

            Task *new = taskNew(priority, taskName);
            dyHeapAdd(list, new, taskCompare);

            printf("The task %s has been added as priorty %d\n", taskName, priority);

            //listPrint(list); debugging

            break;

        case 'g':
            if (dySize(list) > 0)
            {
                Task* task = dyHeapGetMin(list);
                taskPrint(task);
            }
            else
            {
                printf("Your to-do list is empty\n");
            }

            break;

        case 'r':
            if (dySize(list) > 0)
            {
                dyHeapRemoveMin(list, taskCompare);
                printf("Task removed\n");
            }
            else
            {
                printf("Your list is empty\n");
            }

            break;
        
        case 'p':
            
            if (dySize(list) > 0)
            {
                listPrint(list);
            }
            else
            {
                printf("Your list is empty\n");
            }
            
            break;
    }
}

int main()
{
    // Implement
    printf("\n\n** TO-DO LIST APPLICATION **\n\n");
    DynamicArray* list = dyNew(8);
    char command = ' ';
    do
    {
        printf("Press:\n"
               "'l' to load to-do list from a file\n"
               "'s' to save to-do list to a file\n"
               "'a' to add a new task\n"
               "'g' to get the first task\n"
               "'r' to remove the first task\n"
               "'p' to print the list\n"
               "'e' to exit the program\n"
        );
        command = getchar();
        // Eat newlines
        while (getchar() != '\n');
        handleCommand(list, command);
    }
    while (command != 'e');
    dyDelete(list);
    return 0;
}