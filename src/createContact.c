/*******createContact.c********
Author: Ryan Simmons
Last Modified: March 29th, 2019
******************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../includes/contactList.h"

void createContact(FILE *filePtr)
{
    /*Declare a new structure to be written to the disk*/
    struct contact record;

    /*Variable for buffer*/
    char buffer[1000];

    /*Create temporary variables for all of the values*/
    char *firstName;
    char *lastName;
    char *companyName;
    char *email;

    /*Create variable to hold how much data has been written so far*/
    long writtenSoFar = 0;

    /*Create a variable that determines whether or not the user has entered a last name*/
    int entered = 0;

    /*Create a variable that determines whether or not the phone number is good or bad*/
    int pNBad;

    /*Create a variable that determines whether or not the email is valid or not*/
    int emailGood;

    /*Get first name*/
    printf("First Name: ");
    fgets(buffer, 1000, stdin);
    /*Allocate enough space for the string + null character, but NOT the trailing newline character*/
    firstName = malloc(sizeof(char) * strlen(buffer));
    /*Copy all characters except the trailing newline character to the malloc'd string*/
    strncpy(firstName, buffer, strlen(buffer) - 1);
    /*strncpy() does not automatically append null character, so add it on manually*/
    firstName[strlen(buffer) - 1] = '\0';
    
    /*Get last name*/
    printf("Last Name: ");
    fgets(buffer, 1000, stdin);

    /*Check to see if a last name was entered, and set the entered variable accordingly*/
    if (strcmp(buffer, "\n") != 0)
    {
        entered = 1;
    }

    /*Allocate enough space for the string + null character, but NOT the trailing newline character*/
    lastName = malloc(sizeof(char) * strlen(buffer));
    /*Copy all characters except the trailing newline character to the malloc'd string*/
    strncpy(lastName, buffer, strlen(buffer) - 1);
    /*strncpy() does not automatically append null character, so add it on manually*/
    lastName[strlen(buffer) - 1] = '\0';

    /*Get company name*/
    do
    {
        /*If the user enters nothing and they didn't enter a last name, repeat until they enter a company name*/
        printf("Company Name: ");
        fgets(buffer, 1000, stdin);
        if (entered == 0 && strcmp(buffer, "\n") == 0)
            printf("Please enter a company name, as a last name was not entered\n");
    } while (entered == 0 && strcmp(buffer, "\n") == 0);
    /*Allocate enough space for the string + null character, but NOT the trailing newline character*/
    companyName = malloc(sizeof(char) * strlen(buffer));
    /*Copy all characters except the trailing newline character to the malloc'd string*/
    strncpy(companyName, buffer, strlen(buffer) - 1);
    /*strncpy() does not automatically append null character, so add it on manually*/
    companyName[strlen(buffer) - 1] = '\0';

    /*Get phone number*/
    do
    {
        /*Keep asking for phone number until user enters it*/
        printf("Phone Number (enter only numbers): ");
        fgets(buffer, 1000, stdin);
        pNBad = checkPhoneNumber(buffer);
        if (pNBad == 0)
            printf("Invalid phone number, please try again\n");
    } while (pNBad == 0 || strcmp(buffer, "\n") == 0);
    /*Convert phone number in temp string to an integer and store it in the structure*/
    sscanf(buffer, "%ld", &record.phone_number);

    /*Get email*/
    do
    {
        printf("Email: ");
        fgets(buffer, 1000, stdin);
        emailGood = checkEmail(buffer);
        if (strcmp(buffer, "\n") != 0 && emailGood == 0)
            printf("Invalid email, please try again\n");
    } while (strcmp(buffer, "\n") != 0 && emailGood == 0);
    /*Allocate enough space for the string + null character, but NOT the trailing newline character*/
    email = malloc(sizeof(char) * strlen(buffer));
    /*Copy all characters except the trailing newline character to the malloc'd string*/
    strncpy(email, buffer, strlen(buffer) - 1);
    /*strncpy() does not automatically append null character, so add it on manually*/
    email[strlen(buffer) - 1] = '\0';

    /*Confirm if the user wants to add the new contact*/
    do
    {
        printf("Action: ");
        scanf("%s", buffer);
        if (strcmp(buffer, "R") != 0 && strcmp(buffer, "S") != 0)
            printf("Invalid choice, please try again\n");
    } while (strcmp(buffer, "R") != 0 && strcmp(buffer, "S") != 0);
    getchar();

    /*If the user wants to discard changes*/
    if (strcmp(buffer, "R") == 0)
    {
        /*Free dynamically allocated pointers*/
        free(firstName);
        free(lastName);
        free(companyName);
        free(email);
        return;
    }

    /*Calculate positions of each variable and write them to the structure*/
    fseek(filePtr, 0, SEEK_END);
    writtenSoFar = ftell(filePtr);

    /*If the entry is empty, set position = 0, otherwise position is the sum of all data written so far, plus the size of the structure, plus 
    the size of each item in the contact, if it exits, otherwise 0 for that item*/
    record.first_name_posn = (strlen(firstName) == 0) ? 0: writtenSoFar + (sizeof(long) * 6);

    record.last_name_posn = (strlen(lastName) == 0) ? 0: (writtenSoFar + (sizeof(long) * 6) + ((strlen(firstName) == 0) ? 0: (sizeof(char) * (strlen(firstName) + 1))));

    record.company_name_posn = (strlen(companyName) == 0) ? 0: (writtenSoFar + (sizeof(long) * 6) + ((strlen(firstName) == 0) ? 0: (sizeof(char) * (strlen(firstName) + 1))) + ((strlen(lastName) == 0) ? 0: (sizeof(char) * (strlen(lastName) + 1))));

    record.email_posn = (strlen(email) == 0) ? 0: (writtenSoFar + (sizeof(long) * 6) + ((strlen(firstName) == 0) ? 0: (sizeof(char) * (strlen(firstName) + 1))) + ((strlen(lastName) == 0) ? 0: (sizeof(char) * (strlen(lastName) + 1))) + ((strlen(companyName) == 0) ? 0: (sizeof(char) * (strlen(companyName) + 1))));

    record.next = writtenSoFar + (sizeof(long) * 6) + ((strlen(firstName) == 0) ? 0: (sizeof(char) * (strlen(firstName) + 1))) + ((strlen(lastName) == 0) ? 0: (sizeof(char) * (strlen(lastName) + 1))) + ((strlen(companyName) == 0) ? 0: (sizeof(char) * (strlen(companyName) + 1))) + ((strlen(email) == 0) ? 0: (sizeof(char) * (strlen(email) + 1)));

    /*Write the new contact to the file*/
    fwrite(&record, sizeof(struct contact), 1, filePtr);

    /*If the string for any item is empty, don't write that item to the file*/
    if (strlen(firstName) != 0)
        fwrite(firstName, (sizeof(char) * (strlen(firstName) + 1)), 1, filePtr);
    if (strlen(lastName) != 0)
        fwrite(lastName, (sizeof(char) * (strlen(lastName) + 1)), 1, filePtr);
    if (strlen(companyName) != 0)
        fwrite(companyName, (sizeof(char) * (strlen(companyName) + 1)), 1, filePtr);
    if (strlen(email) != 0)
        fwrite(email, (sizeof(char) * (strlen(email) + 1)), 1, filePtr);

    /*Flush the buffer to the file*/
    fflush(filePtr);

    /*Free dynamically allocated pointers*/
    free(firstName);
    free(lastName);
    free(companyName);
    free(email);

    return;
}
