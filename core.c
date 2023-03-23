
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>

#include "core.h"

//////////////////////////////////////
// USER INTERFACE FUNCTIONS
//////////////////////////////////////

// Clear the standard input buffer
void clearInputBuffer(void)
{
    // Discard all remaining char's from the standard input buffer:
    while (getchar() != '\n')
    {
        ; // do nothing!
    }
}

// Wait for user to input the "enter" key to continue
void suspend(void)
{
    printf("<ENTER> to continue...");
    clearInputBuffer();
    putchar('\n');
}

//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

// return an integer value and receives no arguments
int inputInt()
{
    char newLine = 'x';
    int value;
    while (newLine != '\n')
    {
        scanf("%d%c", &value, &newLine);
        if (newLine != '\n')
        {
            clearInputBuffer();
            printf("Error! Input a whole number: ");
        }
    }
    return value;
}

// return a positive integer value and receives no arguments
int  inputIntPositive()
{
    int positiveint = 0;
    while (positiveint < 1)
    {
        positiveint = inputInt();
        if (positiveint < 1)
        {
            printf("ERROR! Value must be > 0: ");
        }
    }
    return positiveint;
}

// return an integer value and receives two arguments
int  inputIntRange(int lowerrange, int upperrange)
{
    int betweenrange = -100;
    while (betweenrange < lowerrange || upperrange < betweenrange)
    {
        betweenrange = inputInt();
        if (betweenrange < lowerrange || upperrange < betweenrange)
        {
            printf("ERROR! Value must be between %d and %d inclusive: ", lowerrange, upperrange);
        }
    }
    return betweenrange;
}

// return a single character value and receives one argument(string)
char inputCharOption(char str[])
{
    int i = 0;
    char match = '0';
    char buffer;
    while (str[i] != match)
    {
        scan:
        scanf("%c%c", &match, &buffer);
        if (buffer != '\n')
        {
            printf("ERROR: Character must be one of [yn]: ");
            clearInputBuffer();
            goto scan;
        }
        for (i = 0; str[i] != '\0'; i++)
        {
            if (str[i] == match)
            {
                return match;
            }
        }
        printf("ERROR: Character must be one of [yn]: ");
    }
    return 0;
}

// this function obtain input for a string value with number of characters in the range
void  inputCString(char* Cstring, int minchar, int maxchar)
{
    int i, sizeofstring = 0;
    if (minchar == maxchar)
    {
        while (sizeofstring != minchar)
        {
            sizeofstring = 0;
            scanf("%[^\n]", Cstring);
            clearInputBuffer();
            for (i = 0; Cstring[i] != '\0'; i++)
            {
                sizeofstring++;
            }
            if (sizeofstring != minchar)
            {
                printf("ERROR: String length must be exactly %d chars: ", minchar);
            }
        }
    }
    else
    {
        while (sizeofstring > maxchar || sizeofstring < minchar)
        {
            sizeofstring = 0;
            scanf("%[^\n]", Cstring);
            clearInputBuffer();
            for (i = 0; Cstring[i] != '\0'; i++)
            {
                sizeofstring++;
            }
            if (sizeofstring > maxchar)
            {
                printf("ERROR: String length must be no more than %d chars: ", maxchar);
            }
            else if (sizeofstring < minchar)
            {
                printf("ERROR: String length must be between %d and %d chars: ", minchar, maxchar);
            }
        }
    }
}

//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////

// this function is to display an array of 10-character digits as a formatted phone number
void  displayFormattedPhone(const char* Cstring)
{
    int i = 0, sizeofstring = 0;
    if (Cstring == NULL)
    {
        printf("(___)___-____");
    }
    else if (Cstring[i] != '\0')
    {
        for (i = 0; Cstring[i] != '\0'; i++)
        {
            sizeofstring++;
        }
    }
    if (sizeofstring == 10)
    {
        if ((Cstring[0] < 48 || Cstring[0] > 57) || (Cstring[1] < 48 || Cstring[1] > 57) || (Cstring[2] < 48 || Cstring[2] > 57) || (Cstring[3] < 48 || Cstring[3] > 57) || (Cstring[4] < 48 || Cstring[4] > 57) || (Cstring[5] < 48 || Cstring[5] > 57) || (Cstring[6] < 48 || Cstring[6] > 57) || (Cstring[7] < 48 || Cstring[7] > 57) || (Cstring[8] < 48 || Cstring[8] > 57) || (Cstring[9] < 48 || Cstring[9] > 57))
        {
            printf("(___)___-____");
        }
        else
        {
            printf("(");
            for (i = 0; Cstring[i] != '\0'; i++)
            {
                printf("%c", Cstring[i]);
                if (i == 2)
                {
                    printf(")");
                }
                if (i == 5)
                {
                    printf("-");
                }
            }
        }
    }
    else if (Cstring != NULL)
        printf("(___)___-____");
}