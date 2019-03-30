/*****readDataToMemory.c*******
Author: Ryan Simmons
Course: CIS*2500
Last Modified: March 29th, 2019
******************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../includes/contactList.h"

char *readDataToMemory(FILE *filePtr)
{
    /*Variable to store the number of entries in the file*/
    int contactCount = 0;

    /*Temporary structure used to read in data*/
    struct contact tempStruct;

    /*Counting variables*/
    int i;
    int j = 0;

    /*char to test values*/
    char testChar;

    /*buffer to store strings in before they are copied to a structure*/
    char buffer[1000];

    /*Read through the file and count the number of contacts*/
    fseek(filePtr, 0, SEEK_SET);
    while (feof(filePtr) == 0)
    {
        ++contactCount;
        fread(&tempStruct, sizeof(struct contact), 1, filePtr);
        fseek(filePtr, tempStruct.next, SEEK_SET);
    }

    /*Create array to hold contact data based on the number of contacts in the file*/
    struct contactData contactArray[contactCount];

    /*Read the data from the contact file into contactArray*/
    fseek(filePtr, 0, SEEK_SET);
    for (i = 0; feof(filePtr) == 0; ++i)
    {
        /*Read in a contact from file*/
        fread(&tempStruct, sizeof(struct contact), 1, filePtr);

        /*Set the contact's phone number in the array to the value in file*/
        contactArray[i].phone_number = tempStruct.phone_number;

        /*Seek to the first name's position*/
        fseek(filePtr, tempStruct.first_name_posn, SEEK_SET);
        if (tempStruct.first_name_posn != 0)
        {
            /*Read in characters into a buffer until the end of the string is reached*/
            do
            {
                fread(&testChar, sizeof(char), 1, filePtr);
                buffer[j] = testChar;
                ++j;
            } while (testChar != '\0');
            j = 0;

            /*Allocate enough space for the string to store the first name*/
            contactArray[i].first_name = malloc(sizeof(char) * (strlen(buffer) + 1));
            /*Copy the first name to the string in the array*/
            strcpy(contactArray[i].first_name, buffer);
        }
        else
        {
            /*If the first name is not given, make the value for the first name in the array an empty string*/
            contactArray[i].first_name = malloc(sizeof(char));
            strcpy(contactArray[i].first_name, "");
        }

        /*Repeat this process for all the other values for the contact*/
        
        fseek(filePtr, tempStruct.last_name_posn, SEEK_SET);
        if (tempStruct.last_name_posn != 0)
        {
            do
            {
                fread(&testChar, sizeof(char), 1, filePtr);
                buffer[j] = testChar;
                ++j;
            } while (testChar != '\0');
            j = 0;

            contactArray[i].last_name = malloc(sizeof(char) * (strlen(buffer) + 1));
            strcpy(contactArray[i].last_name, buffer);
        }
        else
        {
            contactArray[i].last_name = malloc(sizeof(char));
            strcpy(contactArray[i].last_name, "");
        }

        fseek(filePtr, tempStruct.company_name_posn, SEEK_SET);
        if (tempStruct.company_name_posn != 0)
        {
            do
            {
                fread(&testChar, sizeof(char), 1, filePtr);
                buffer[j] = testChar;
                ++j;
            } while (testChar != '\0');
            j = 0;

            contactArray[i].company_name = malloc(sizeof(char) * (strlen(buffer) + 1));
            strcpy(contactArray[i].company_name, buffer);
        }
        else
        {
            contactArray[i].company_name = malloc(sizeof(char));
            strcpy(contactArray[i].company_name, "");
        }

        fseek(filePtr, tempStruct.email_posn, SEEK_SET);
        if (tempStruct.email_posn != 0)
        {
            do
            {
                fread(&testChar, sizeof(char), 1, filePtr);
                buffer[j] = testChar;
                ++j;
            } while (testChar != '\0');
            j = 0;

            contactArray[i].email = malloc(sizeof(char) * (strlen(buffer) + 1));
            strcpy(contactArray[i].email, buffer);
        }
        else
        {
            contactArray[i].email = malloc(sizeof(char));
            strcpy(contactArray[i].email, "");
        }

        /*Seek to the position of the next contact, and start the process all over again for the next contact in the file*/
        fseek(filePtr, tempStruct.next, SEEK_SET);
    }

    /*Return the array full of contacts*/
    return contactArray;
}