#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NUMPROD 6      // Specify number of productions
#define MAXPRODLEN 10  // Maximum length of a single production
#define MAX 50         // Maximum size of input string and stack

// Specify the productions here.
char productions[NUMPROD][MAXPRODLEN] = {
    "E=E+E",
    "E=E*E",
    "E=i",
    "E=(E)",
    "E=E-E",
    "E=E/E"
};

char *ptr_prod = &productions[0][0]; // Declare a pointer to the productions table
char input[MAX] = {0}, stack[MAX] = {0};
short top = -1, ip_ptr = 0; // pointers to the top of the stack and input string

// Prototypes of shift & reduce
void shift(char symb);
void reduce(int prodno, char *stackpos); // takes production number and handle location as args

int main()
{
    printf("Enter the string to be parsed: ");
    scanf("%[^\n]", input);
    getchar(); // remove extra new line from i/p stream.

    printf("\nSHIFT-REDUCE PARSING\n");
    printf("Stack\t\tInput\t\tAction\n");
    printf("-----\t\t-----\t\t------\n");

    // Parse input
    while (input[ip_ptr] != '\0') // till the end of the input
    {
        shift(input[ip_ptr++]);

        // continuously reduce
        for (int j = 0; j < NUMPROD; j++)
        {
            for (int i = 0; i < NUMPROD; i++)
            {
                // find the beginning of the handle in the stack
                char *pos = strstr(stack, (ptr_prod + i * MAXPRODLEN + 2));
                if (pos != NULL)
                {
                    reduce(i, pos);
                }
            }
        }
    }

    // After the input is finished
    if (top == 0 && stack[top] == 'E')
    {
        printf("Input accepted\n");
    }
    else
    {
        printf("Input rejected\n");
    }

    return 0;
}

void shift(char c)
{
    stack[++top] = c;
    printf("%s\t\t%s\t\tShifted %c to stack\n", stack, (input + ip_ptr), c);
}

void reduce(int prodno, char *stackpos)
{
    int len = strlen(stackpos);
    top -= len;
    bzero((stack + top + 1), len);

    stack[++top] = productions[prodno][0];
    printf("%s\t\t%s\t\tReduced by the production %s\n",
           stack, (input + ip_ptr), productions[prodno]);
}
