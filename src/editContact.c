/********editContact.c*********
Author: Ryan Simmons
Course: CIS*2500
Last Modified: March 29th, 2019
******************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../includes/contactList.h"

void editContact(struct contactData *contactArray, FILE **filePtrPtr, int contactNumber, int numElements)
{
    /*Temporary structure for checking values in the file*/
    struct contact tempStruct;

    /*Variable that determines whether or not input is good*/
    int inputGood = 0;

    /*Buffer to hold input*/
    char buffer[1000];

    /*Variable to hold phone number*/
    unsigned long phoneNumber;

    /*Pointer for the email*/
    char *email = NULL;

    /*Counting variable*/
    int i;

    /*Variable to determine how much has been written so far*/
    long writtenSoFar;

    /*Variable to store the old structure in case the user decides to discard changes*/
    struct contactData tempData;
    tempData = contactArray[contactNumber];

    /*Print out the first name, last name, company name for the contact*/
    printf("First Name: %s\n", contactArray[contactNumber].first_name);
    printf("Last Name: %s\n", contactArray[contactNumber].last_name);
    printf("Company Name %s\n", contactArray[contactNumber].company_name);

    /*Prompt the user for a phone number*/
    do
    {
        /*If the user enter a new phone number, check to make sure that it is correct*/
        printf("Phone Number (enter only numbers): ");
        fgets(buffer, 1000, stdin);
        inputGood = checkPhoneNumber(buffer);
        if (strcmp(buffer, "\n") != 0 && inputGood == 0)
            printf("Invalid phone number, please try again\n");
    } while (strcmp(buffer, "\n") != 0 && inputGood == 0);

    /*If the user entered a phone number, convert the string to an unsigned long, and edit array*/
    if (strcmp(buffer, "\n") != 0)
    {
        sscanf(buffer, "%ld", &phoneNumber);
        contactArray[contactNumber].phone_number = phoneNumber;
    }

    /*Prompt the user for an email*/
    do
    {
        printf("Email: ");
        fgets(buffer, 1000, stdin);
        inputGood = checkEmail(buffer);
        if (strcmp(buffer, "\n") != 0 && inputGood == 0)
            printf("Invalid email, please try again\n");
    } while (strcmp(buffer, "\n") != 0 && inputGood == 0);

    /*Allocate enough space for the string + null character, but NOT the trailing newline character*/
    email = malloc(sizeof(char) * strlen(buffer));
    
    /*Copy all characters except the trailing newline character to the malloc'd string*/
    strncpy(email, buffer, strlen(buffer) - 1);
    /*strncpy() does not automatically append null character, so add it on manually*/
    email[strlen(buffer) - 1] = '\0';

    /*Free, then allocate the array's email pointer*/
    free(contactArray[contactNumber].email);
    contactArray[contactNumber].email = malloc(sizeof(char) * (strlen(email) + 1));
    /*Edit the array*/
    strcpy(contactArray[contactNumber].email, email);

    /*Prompt the user to input an action*/
    do
    {
        printf("Action: ");
        scanf("%s", buffer);
        if (strcmp(buffer, "R") != 0 && strcmp(buffer, "S") != 0 && strcmp(buffer, "D") != 0)
            printf("Invalid choice, please try again\n");
    } while (strcmp(buffer, "R") != 0 && strcmp(buffer, "S") != 0 && strcmp(buffer, "D") != 0);
    getchar();

    /*If the user wants to discard changes*/
    if (strcmp(buffer, "R") == 0)
    {
        contactArray[contactNumber] = tempData;
        free(email);
        return;
    }
    /*If the user wants to delete the contact*/
    else if (strcmp(buffer, "D") == 0)
    {
        deleteContact(contactArray, filePtrPtr, contactNumber, numElements);
        /*Return to the full contact list when deletion is done*/
        return;
    }

    /*Rewrite the file using data from the new array*/
    /*Close and reopen the file in write mode*/
    fclose(*filePtrPtr);
    *filePtrPtr = fopen("myContactList.db", "wb+");

    /*Use a loop to rewrite all the contact data*/
    for (i = 0; i < numElements; ++i)
    {
        /*Determine how much has been written so far*/
        fseek(*filePtrPtr, 0, SEEK_END);
        writtenSoFar = ftell(*filePtrPtr);

        /*Assign phone number to structure*/
        tempStruct.phone_number = contactArray[i].phone_number;

        /*If the entry is empty, set position = 0, otherwise position is the sum of all data written so far, plus the size of the structure, plus 
        the size of each item in the contact, if it exits, otherwise 0 for that item*/
        tempStruct.first_name_posn = (strlen(contactArray[i].first_name) == 0) ? 0: writtenSoFar + (sizeof(long) * 6);

        tempStruct.last_name_posn = (strlen(contactArray[i].last_name) == 0) ? 0: (writtenSoFar + (sizeof(long) * 6) + ((strlen(contactArray[i].first_name) == 0) ? 0: (sizeof(char) * (strlen(contactArray[i].first_name) + 1))));

        tempStruct.company_name_posn = (strlen(contactArray[i].company_name) == 0) ? 0: (writtenSoFar + (sizeof(long) * 6) + ((strlen(contactArray[i].first_name) == 0) ? 0: (sizeof(char) * (strlen(contactArray[i].first_name) + 1))) + ((strlen(contactArray[i].last_name) == 0) ? 0: (sizeof(char) * (strlen(contactArray[i].last_name) + 1))));

        tempStruct.email_posn = (strlen(contactArray[i].email) == 0) ? 0: (writtenSoFar + (sizeof(long) * 6) + ((strlen(contactArray[i].first_name) == 0) ? 0: (sizeof(char) * (strlen(contactArray[i].first_name) + 1))) + ((strlen(contactArray[i].last_name) == 0) ? 0: (sizeof(char) * (strlen(contactArray[i].last_name) + 1))) + ((strlen(contactArray[i].company_name) == 0) ? 0: (sizeof(char) * (strlen(contactArray[i].company_name) + 1))));

        tempStruct.next = writtenSoFar + (sizeof(long) * 6) + ((strlen(contactArray[i].first_name) == 0) ? 0: (sizeof(char) * (strlen(contactArray[i].first_name) + 1))) + ((strlen(contactArray[i].last_name) == 0) ? 0: (sizeof(char) * (strlen(contactArray[i].last_name) + 1))) + ((strlen(contactArray[i].company_name) == 0) ? 0: (sizeof(char) * (strlen(contactArray[i].company_name) + 1))) + ((strlen(contactArray[i].email) == 0) ? 0: (sizeof(char) * (strlen(contactArray[i].email) + 1)));

        /*Write the new contact to the file*/
        fwrite(&tempStruct, sizeof(struct contact), 1, *filePtrPtr);

        /*If the string for any item is empty, don't write that item to the file*/
        if (strlen(contactArray[i].first_name) != 0)
            fwrite(contactArray[i].first_name, (sizeof(char) * (strlen(contactArray[i].first_name) + 1)), 1, *filePtrPtr);
        if (strlen(contactArray[i].last_name) != 0)
            fwrite(contactArray[i].last_name, (sizeof(char) * (strlen(contactArray[i].last_name) + 1)), 1, *filePtrPtr);
        if (strlen(contactArray[i].company_name) != 0)
            fwrite(contactArray[i].company_name, (sizeof(char) * (strlen(contactArray[i].company_name) + 1)), 1, *filePtrPtr);
        if (strlen(contactArray[i].email) != 0)
            fwrite(contactArray[i].email, (sizeof(char) * (strlen(contactArray[i].email) + 1)), 1, *filePtrPtr);
    }

    /*Free the email pointer if it was allocated*/
    if (email != NULL)
        free(email);
    
    /*Flush the file buffer*/
    fflush(*filePtrPtr);

    /*Re-open the file in append mode*/
    fclose(*filePtrPtr);
    *filePtrPtr = openFile();

    return;
}