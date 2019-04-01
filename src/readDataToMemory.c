/*****readDataToMemory.c*******
Author: Ryan Simmons
Course: CIS*2500
Last Modified: March 29th, 2019
******************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../includes/contactList.h"

struct contactData *readDataToMemory(FILE *filePtr, int *numElements)
{
    /*Temporary structure used to read in data*/
    struct contact tempStruct;

    /*Structure array for holding data*/
    struct contactData *contactArray = NULL;

    /*Counting variables*/
    int i;
    int j = 0;

    /*char to test values*/
    char testChar;

    /*buffer to store strings in before they are copied to a structure*/
    char buffer[1000];

    /*Integer to store the number of elements successfully read using fread*/
    int numRead;

    /*Set numElements to zero*/
    *numElements = 0;

    /*Read through the file and count the number of contacts*/
    fseek(filePtr, 0, SEEK_SET);
    while (feof(filePtr) == 0)
    {
        numRead = fread(&tempStruct, sizeof(struct contact), 1, filePtr);
        if (numRead == 1)
        {
            ++(*numElements);
            fseek(filePtr, tempStruct.next, SEEK_SET);
        }
    }

    /*Allocate the required number of spaces to the contactArray, if numElements is not 0*/
    if (*numElements != 0)
    {
        contactArray = malloc(sizeof(struct contactData) * (*numElements));
    }
    /*Read the data from the contact file into contactcontactArray*/
    fseek(filePtr, 0, SEEK_SET);
    for (i = 0; feof(filePtr) == 0; ++i)
    {
        /*Read in a contact from file*/
        numRead = fread(&tempStruct, sizeof(struct contact), 1, filePtr);

        if (numRead == 1)
        {
            /*Set the contact's phone number in the contactArray to the value in file*/
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
                /*Copy the first name to the string in the contactArray*/
                strcpy(contactArray[i].first_name, buffer);
            }
            else
            {
                /*If the first name is not given, make the value for the first name in the contactArray an empty string*/
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
    }

    return contactArray;
}