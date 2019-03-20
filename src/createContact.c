/*******createContact.c********
Author: Ryan Simmons
Course: CIS*2500
Last Modified: March 13th, 2019
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
    /*Allocate enough space for the string + null character, but NOT the trailing newline character*/
    lastName = malloc(sizeof(char) * strlen(buffer));
    /*Copy all characters except the trailing newline character to the malloc'd string*/
    strncpy(lastName, buffer, strlen(buffer) - 1);
    /*strncpy() does not automatically append null character, so add it on manually*/
    lastName[strlen(buffer) - 1] = '\0';

    /*Get company name*/
    printf("Company Name: ");
    fgets(buffer, 1000, stdin);
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
    } while (strcmp(buffer, "\n") == 0);
    /*Convert phone number in temp string to an integer and store it in the structure*/
    sscanf(buffer, "%ld", &record.phone_number);

    /*Get email*/
    printf("Email: ");
    fgets(buffer, 1000, stdin);
    /*Allocate enough space for the string + null character, but NOT the trailing newline character*/
    email = malloc(sizeof(char) * strlen(buffer));
    /*Copy all characters except the trailing newline character to the malloc'd string*/
    strncpy(email, buffer, strlen(buffer) - 1);
    /*strncpy() does not automatically append null character, so add it on manually*/
    email[strlen(buffer) - 1] = '\0';

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