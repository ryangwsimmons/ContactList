/*******sortContacts.c*********
Author: Ryan Simmons
Last Modified: March 29th, 2019
******************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../includes/contactList.h"

void sortContacts(struct contactData *contacts, int numElements)
{
    qsort(contacts, numElements, sizeof(struct contactData), compareContacts);
}

int compareContacts(const void *a, const void *b)
{
    /*Strings for storing whichever names need to be compared*/
    char *str1;
    char *str2;

    /*structs to hold the values of a and b*/
    struct contactData *contactA = (struct contactData *)a;
    struct contactData *contactB = (struct contactData *)b;

    /*Integer to store comparison between str1 and str2*/
    int compareValue;

    /*Check to see if a has a last name, and assign a value to str1 accordingly*/
    if (strcmp(contactA->last_name, "") == 0)
    {
        str1 = malloc(sizeof(char) * (strlen(contactA->company_name) + 1));
        strcpy(str1, contactA->company_name);
    }
    else
    {
        str1 = malloc(sizeof(char) * (strlen(contactA->last_name) + 1));
        strcpy(str1, contactA->last_name);
    }
    
    /*Check to see if b has a last name, and assign a value to str2 accordingly*/
    if (strcmp(contactB->last_name, "") == 0)
    {
        str2 = malloc(sizeof(char) * (strlen(contactB->company_name) + 1));
        strcpy(str2, contactB->company_name);
    }
    else
    {
        str2 = malloc(sizeof(char) * (strlen(contactB->last_name) + 1));
        strcpy(str2, contactB->last_name);
    }

    /*Store comparison value in compareValue*/
    compareValue = strcmp(str1, str2);

    /*Free dynamically allocated variables*/
    free(str1);
    free(str2);

    /*Return comparison value*/
    return compareValue;
}
