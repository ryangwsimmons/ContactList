/*****getNameFirstLetter.c*****
Author: Ryan Simmons
Course: CIS*2500
Last Modified: March 29th, 2019
******************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../includes/contactList.h"

char getNameFirstLetter(struct contactData contact)
{
    /*string for storing name*/
    char *str;

    /*character for storing the first letter of the string*/
    char firstLetter;

    /*Check to see if contact has a last name, and assign a value to str accordingly*/
    if (strcmp(contact.last_name, "") == 0)
    {
        str = malloc(sizeof(char) * (strlen(contact.company_name) + 1));
        strcpy(str, contact.company_name);
    }
    else
    {
        str = malloc(sizeof(char) * (strlen(contact.last_name) + 1));
        strcpy(str, contact.last_name);
    }

    /*Get the first letter from the string*/
    firstLetter = toupper(str[0]);

    /*Free dynamically allocated memory*/
    free(str);

    /*Return first letter*/
    return firstLetter;
}