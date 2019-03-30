/********testMain.c************
Author: Ryan Simmons
Course: CIS*2500
Last Modified: March 29th, 2019
******************************/
#include <stdio.h>
#include <string.h>
#include "../includes/contactList.h"

int main()
{
    /*Variable for deciding whether or not the user wishes to enter a new contact*/
    char contactDecision[4];

    /*Pointer for file*/
    FILE *filePtr = openFile();

    do
    {
        do
        {
            /*Ask the user if they wish to enter a new contact*/
            printf("Do you wish to enter a new contact (Yes or No)?: ");
            scanf("%s", contactDecision);
            getc(stdin);

            /*If the user wishes to enter a new contact*/
            if (strcmp(contactDecision, "Yes") == 0)
            {
                createContact(filePtr);
            }
            /*If the user enters neither yes nor no*/
            else if (strcmp(contactDecision, "Yes") != 0 && strcmp(contactDecision, "No") != 0)
            {
                printf("Invalid input\n\n");
            }
        } while (strcmp(contactDecision, "No") != 0);

        /*Ask the user if they want to retrieve a contact*/
        printf("Do you wish to retrieve a contact (Yes or No)?: ");
        scanf("%s", contactDecision);
        getc(stdin);

        /*If the user wishes to retrieve a contact*/
        if (strcmp(contactDecision, "Yes") == 0)
        {
            retrieveContact(filePtr);
        }
        /*If the user enters neither yes nor no*/
        else if (strcmp(contactDecision, "Yes") != 0 && strcmp(contactDecision, "No") != 0)
        {
            printf("Invalid input\n\n");
        }
    } while (strcmp(contactDecision, "No") != 0);

    fclose(filePtr);
    return 0;
}