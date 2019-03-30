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
    struct contactData *contactArray;

    /*Counting variable*/
    int i = 0;

    /*Integer to hold the contact number that the user wishes to look at*/
    int contactSelected;

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
            contactArray = readDataToMemory(filePtr);
            sortContacts(contactArray);
            printf("Number of Contacts = %d\n", sizeof(contactArray) / sizeof(struct contactData));

            /*Print the contacts*/
            while (i < sizeof(contactArray) / sizeof(struct contactData))
            {
                if (i == 0 || getNameFirstLetter(contactArray[i]) != getNameFirstLetter(contactArray[i - 1]))
                {
                    printf("%c\n", getNameFirstLetter(contactArray[i]));
                }
                printf("\t %d. %s\n", i + 1, (strcmp(contactArray[i].last_name, "") == 0) ? contactArray[i].company_name : contactArray[i].last_name);
            }

            /*Prompt the user to input an action*/
            printf("Action: ");
            scanf("%s", menuChoice);
        }
        /*If the user asks to look at a contact*/
        else if (isdigit(menuChoice[0]) != 0)
        {
            /*Get the integer for the contact selected from the string*/
            sscanf(menuChoice, "%d", &contactSelected);

            /*Print out the contact details*/
            printf("Contact #%d\n", contactSelected);
            printf("First Name: %s\n", contactArray[contactSelected - 1].first_name);
            printf("Last Name: %s\n", contactArray[contactSelected - 1].last_name);
            printf("Company Name: %s\n", contactArray[contactSelected - 1].company_name);
            printf("Phone Number: %ld\n", contactArray[contactSelected - 1].phone_number);
            printf("Email: %s\n", contactArray[contactSelected - 1].email);
            
            /*Prompt the user to input an action*/
            printf("Action: ");
            scanf("%s", menuChoice);
        }
        /*If the user wants to add a new contact*/
        else if (strcmp(menuChoice, "A") == 0)
        {
            createContact(filePtr);
        }
    } while (strcmp(menuChoice, "X") != 0);
    
}