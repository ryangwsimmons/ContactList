/******retrieveContact.c*******
Author: Ryan Simmons
Course: CIS*2500
Last Modified: March 13th, 2019
******************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../includes/contactList.h"

void retrieveContact(FILE *filePtr)
{
    /*Declare temporary string for inputting phone number
    and storing contact data if/when it has been found*/
    char temp[1000];

    /*Declare variable for phone number*/
    unsigned long phoneNumber;

    /*Temporary structure for holding the contact records,
    to compare phone numbers and print contact as necessary*/
    struct contact tempStruct;

    /*Variable to hold the value of the position of the next record*/
    long next;

    /*Variable that determines whether or not the requested contact has been found*/
    int found = 0;

    /*Counting variable for loops*/
    int i = 0;

    /*Variable for reading in individual characters of a string*/
    char testChar;

    /*Get phone number*/
    do
    {
        /*Keep asking for phone number until user enters it*/
        printf("Phone Number: ");
        fgets(temp, 1000, stdin);
    } while (strcmp(temp, "\n") == 0);
    /*Convert phone number in temp string to an integer and store it in the structure*/
    sscanf(temp, "%ld", &phoneNumber);

    /*Try to find the contact*/
    next = 0;
    do
    {
        fseek(filePtr, next, SEEK_SET);
        fread(&tempStruct, sizeof(struct contact), 1, filePtr);

        if (tempStruct.phone_number == phoneNumber)
        {
            found = 1;
        }
        else
        {
            next = tempStruct.next;
        }
    } while (feof(filePtr) == 0 && found == 0);
    
    /*If the contact was not found*/
    if (found == 0)
    {
        printf("No match found.\n");
    }
    /*If the contact was found*/
    else
    {
        /*Read in and print the first name*/
        fseek(filePtr, tempStruct.first_name_posn, SEEK_SET);

        /*For each item, only attempt to read it in if it isn't empty; 
        the string is empty if its position is = 0*/
        if (tempStruct.first_name_posn != 0)
        {
            do
            {
                fread(&testChar, sizeof(char), 1, filePtr);
                temp[i] = testChar;
                ++i;
            } while (testChar != '\0');
            i = 0;
        }
        else
        {
            strcpy(temp, "");
        }
        
        printf("First Name: %s\n", temp);

        /*Read in and print the last name*/
        fseek(filePtr, tempStruct.last_name_posn, SEEK_SET);

        if (tempStruct.last_name_posn != 0)
        {
            do
            {
                fread(&testChar, sizeof(char), 1, filePtr);
                temp[i] = testChar;
                ++i;
            } while (testChar != '\0');
            i = 0;
        }
        else
        {
            strcpy(temp, "");
        }
        
        printf("Last Name: %s\n", temp);

        /*Read in and print the company name*/
        fseek(filePtr, tempStruct.company_name_posn, SEEK_SET);

        if (tempStruct.company_name_posn != 0)
        {
            do
            {
                fread(&testChar, sizeof(char), 1, filePtr);
                temp[i] = testChar;
                ++i;
            } while (testChar != '\0');
            i = 0;
        }
        else
        {
            strcpy(temp, "");
        }

        printf("Company Name: %s\n", temp);

        /*Print the phone number*/
        printf("Phone Number: %ld\n", tempStruct.phone_number);

        /*Read in and print the email*/
        fseek(filePtr, tempStruct.email_posn, SEEK_SET);

        if (tempStruct.email_posn != 0)
        {
            do
            {
                fread(&testChar, sizeof(char), 1, filePtr);
                temp[i] = testChar;
                ++i;
            } while (testChar != '\0');
            i = 0;
        }
        else
        {
            strcpy(temp, "");
        }

        printf("Email: %s\n", temp);
    }

    return;
}