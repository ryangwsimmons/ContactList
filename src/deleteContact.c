/********deleteContact.c*******
Author: Ryan Simmons
Last Modified: March 29th, 2019
******************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../includes/contactList.h"

void deleteContact(struct contactData *contactArray, FILE **filePtrPtr, int contactNumber, int numElements)
{
    /*Structure to temporary hold values; needed for re-writing database*/
    struct contact tempStruct;

    /*Counting variable*/
    int i;

    /*Variable to determine how much has been written so far*/
    long writtenSoFar;

    /*Set the selected contact's delete flag to true*/
    contactArray[contactNumber].delete = 1;

    /*Rewrite the file using data from the new array*/
    /*Close and reopen the file in write mode*/
    fclose(*filePtrPtr);
    *filePtrPtr = fopen("myContactList.db", "wb+");

    /*Use a loop to rewrite all the contact data, except for the contact that has been flagged for deletion*/
    for (i = 0; i < numElements; ++i)
    {
        if (contactArray[i].delete == 0)
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
    }

    /*Flush the file buffer*/
    fflush(*filePtrPtr);

    /*Re-open the file in append mode*/
    fclose(*filePtrPtr);
    *filePtrPtr = openFile();

    return;
}
