/*******createContact.c********
Author: Ryan Simmons
Course: CIS*2500
Last Modified: March 29th, 2019
******************************/
#include <stdio.h>
#include <string.h>
#include "../includes/contactList.h"

int checkEmail(char *email)
{
    /*Create variables for determining whether or not an email is valid*/
    int emailGood = 0;
    int atCount = 0;

    /*Counting variables*/
    int i;
    int j;

    /*Check to see if an email is valid*/
    for (i = 0; i < strlen(email); ++i)
    {
        /*If an email has an @ in it, search for a . after the @*/
        if (email[i] == '@')
        {
            /*If an @ is found, increase the counter*/
            ++atCount;
            if (i != strlen(email) - 1 && i != 0)
            {
                /*If not at the end of the string, search for a .*/
                for (j = i + 1; j < strlen(email); ++j)
                {
                    /*If a . is found, and it's not the last character in the string, indicate that the string is good*/
                    if (email[j] == '.' && j != strlen(email) - 1 && email[j - 1] != '@')
                        emailGood = 1;
                }
            }
        }
    }

    /*Use the number of @ characters in the string along with the emailGood 
    variable to determine if a string is good, then return accordingly*/
    if (emailGood != 0 && atCount == 1)
        return 1;
    else
        return 0;
}