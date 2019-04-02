/**************main.c**********
Author: Ryan Simmons
Course: CIS*2500
Last Modified: March 29th, 2019
******************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../includes/contactList.h"

int main()
{
    /*String for deciding on what menu option should be selected*/
    char menuChoice[1000];

    /*Array for storing contacts from file*/
    struct contactData *contactArray = NULL;

    /*Counting variable*/
    int i = 0;

    /*Integer to hold the contact number that the user wishes to look at*/
    int contactSelected;

    /*Variable to hold the number of elements in the array*/
    int numElements;

    /*Open the file*/
    FILE *filePtr = openFile();

    /*Set the default menu to be the contacts menu*/
    strcpy(menuChoice, "R");

    /*Enter the menu system*/
    do
    {
        /*If the user is at the full contacts list*/
        if (strcmp(menuChoice, "R") == 0)
        {
            if (contactArray != NULL)
            {
                for (i = 0; i < numElements; ++i)
                {
                    free(contactArray[i].first_name);
                    free(contactArray[i].last_name);
                    free(contactArray[i].company_name);
                    free(contactArray[i].email);
                }
                free(contactArray);
            }
            i = 0;
            contactArray = readDataToMemory(filePtr, &numElements);
            sortContacts(contactArray, numElements);
            printf("Number of Contacts = %d\n", numElements);

            /*Print the contacts*/
            while (i < numElements)
            {
                if (i == 0 || (getNameFirstLetter(contactArray[i]) != getNameFirstLetter(contactArray[i - 1])))
                {
                    printf("%c\n", getNameFirstLetter(contactArray[i]));
                }
                printf("\t %d. %s %s\n", i + 1, (strcmp(contactArray[i].last_name, "") == 0) ? contactArray[i].company_name : contactArray[i].first_name, (strcmp(contactArray[i].last_name, "") == 0) ? "" : contactArray[i].last_name);
                ++i;
            }
            i = 0;

            /*Prompt the user to input an action*/
            do
            {
                printf("Action: ");
                scanf("%s", menuChoice);
                if (strcmp(menuChoice, "A") != 0 && strcmp(menuChoice, "X") != 0 && isdigit(menuChoice[0]) == 0)
                    printf("Invalid choice, please try again\n");
            } while (strcmp(menuChoice, "A") != 0 && strcmp(menuChoice, "X") != 0 && isdigit(menuChoice[0]) == 0);
            getchar();
        }
        /*If the user asks to look at a contact*/
        else if (isdigit(menuChoice[0]) != 0)
        {
            /*Get the integer for the contact selected from the string*/
            sscanf(menuChoice, "%d", &contactSelected);
            if (contactSelected > numElements)
            {
                printf("Invalid contact number, please try again\n");
                strcpy(menuChoice, "R");
            }
            else
            {
                /*Print out the contact details*/
                printf("Contact #%d\n", contactSelected);
                printf("First Name: %s\n", contactArray[contactSelected - 1].first_name);
                printf("Last Name: %s\n", contactArray[contactSelected - 1].last_name);
                printf("Company Name: %s\n", contactArray[contactSelected - 1].company_name);
                printf("Phone Number: %ld\n", contactArray[contactSelected - 1].phone_number);
                printf("Email: %s\n", contactArray[contactSelected - 1].email);
                
                /*Prompt the user to input an action*/
                do
                {
                    printf("Action: ");
                    scanf("%s", menuChoice);
                    if (strcmp(menuChoice, "R") != 0 && strcmp(menuChoice, "E") != 0 && strcmp(menuChoice, "D") != 0)
                        printf("Invalid choice, please try again\n");
                } while (strcmp(menuChoice, "R") != 0 && strcmp(menuChoice, "E") != 0 && strcmp(menuChoice, "D") != 0);
                getchar();
            }
        }
        /*If the user wants to add a new contact*/
        else if (strcmp(menuChoice, "A") == 0)
        {
            createContact(filePtr);
            /*Return to full contact list when creating contact is done*/
            strcpy(menuChoice, "R");
        }
        /*If the user wants to edit a contact*/
        else if (strcmp(menuChoice, "E") == 0)
        {
            editContact(contactArray, &filePtr, contactSelected - 1, numElements);
            /*Return to the full contact list when editing contact is done*/
            strcpy(menuChoice, "R");
        }
        else if (strcmp(menuChoice, "D") == 0)
        {
            deleteContact(contactArray, &filePtr, contactSelected - 1, numElements);
            /*Return to the full contact list when deletion is done*/
            strcpy(menuChoice, "R");
        }
    } while (strcmp(menuChoice, "X") != 0);

    /*Free values in contact array*/
    for (i = 0; i < numElements; ++i)
    {
        free(contactArray[i].first_name);
        free(contactArray[i].last_name);
        free(contactArray[i].company_name);
        free(contactArray[i].email);
    }

    /*Free the array itself*/
    free(contactArray);

    /*Close the file*/
    fclose(filePtr);

    return 0;
}