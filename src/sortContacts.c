/*******sortContacts.c*********
Author: Ryan Simmons
Course: CIS*2500
Last Modified: March 29th, 2019
******************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../includes/contactList.h"

void sortContacts(struct contactData contacts[])
{
    qsort(contacts, sizeof(contacts) / sizeof(struct contactData), sizeof(struct contactData), compareContacts);
}

int compareContacts(const void *a, const void *b)
{
    /*Strings for storing whichever names need to be compared*/
    char *str1;
    char *str2;

    /*Integer to store comparison between str1 and str2*/
    int compareValue;

    /*Check to see if a has a last name, and assign a value to str1 accordingly*/
    if (strcmp(((struct contactData *)a)->last_name, "") == 0)
    {
        str1 = malloc(sizeof(char) * (strlen(((struct contactData *)a)->company_name) + 1));
        strcpy(str1, ((struct contactData *)a)->company_name);
    }
    else
    {
        str1 = malloc(sizeof(char) * (strlen(((struct contactData *)a)->last_name) + 1));
        strcpy(str1, ((struct contactData *)a)->last_name);
    }
    
    /*Check to see if b has a last name, and assign a value to str2 accordingly*/
    if (strcmp(((struct contactData *)b)->last_name, "") == 0)
    {
        str2 = malloc(sizeof(char) * (strlen(((struct contactData *)b)->company_name) + 1));
        strcpy(str2, ((struct contactData *)b)->company_name);
    }
    else
    {
        str2 = malloc(sizeof(char) * (strlen(((struct contactData *)b)->last_name) + 1));
        strcpy(str2, ((struct contactData *)b)->last_name);
    }

    /*Store comparison value in compareValue*/
    compareValue = strcmp(str1, str2);

    /*Free dynamically allocated variables*/
    free(str1);
    free(str2);

    /*Return comparison value*/
    return compareValue;
}