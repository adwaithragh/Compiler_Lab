#include<stdio.h>
#include<string.h>
#include<ctype.h>
#define SIZE 26
#define LENGTH 20
char productions[SIZE][LENGTH]={'\0'};
char firstsets[SIZE][LENGTH]={'\0'};
char NonTerminals[SIZE]={'\0'};
char StartSymbol = '\0';
int num_productions=0;
//Adds a character to a set represented as a string
void set_add(char *set,char elem)
{
    if(!strchr(set,elem))
    {
        int idx = strlen(set);
        set[idx] = elem;
        set[idx+1]='\0';
    }
}
//Finds the union of two sets in set1
void set_union(char *set1,char *set2)
{
    int i=0;
    while(set2[i]!='\0')
        set_add(set1,set2[i++]);
}
//Removes a character from a set represented as string
void set_remove(char *set,char elem)
{
    if(!strchr(set,elem))
        return;
    else
    {   //The index of the element to be removed is calculated
        int idx=strchr(set,elem)-set;
        while (set[idx++])
        {
            set[idx-1]=set[idx];
        }
        set[idx]='\0';
    }
}
//returns set membership
int is_in_set(char *set,char elem)
{
    return strchr(set,elem)!=NULL;
}
//prints a set
void printset(char *set)
{
    int i=0;
    printf("{");
    for(i=0;set[i]!='\0';i++)
    {
        printf("%c",set[i]);
        if(set[i+1]!='\0')
            printf(",");
    }
    printf("}\n");
}
//Calculates the index of a non terminal by its ordinal
int get_index(char NT)
{
    return NT-'A';
}
//Get all productions from user
void read_productions()
{
    printf("Make sure to eliminate left recursion from grammar, else program will crash\n");
    printf("Enter the number of productions.(LHS of first production is taken as start symbol)\n");
    scanf("%d",&num_productions);
    printf("Enter the productions as A=Bc,A=# (Use # for epsilon and = for arrow)\n");
    getchar(); //Remove new line from stdin
    for(int i=0;i<num_productions;i++)
    {
        scanf("%[^\n]",productions[i]);
        getchar(); //Remove new line from stdin
        set_add(NonTerminals,productions[i][0]);//Add LHS to set of NT
    }
    StartSymbol = productions[0][0];
}
//Calculates and stores the first sets (indexed by ordinal position of chars)
void calc_first(char symbol,char *set)
{
    if(symbol=='\0')
        return;
    if(!isupper(symbol)) //Only uppercase letters are non terminals
    {
        if(is_in_set(set,'#'))//if epsilon is already in the set, remove it since there is
            set_remove(set,'#');// a terminal or another epsilon in RHS
        set_add(set,symbol);
    }
    else
    {
        for(int i=0;i<num_productions;i++)
        {
            if(productions[i][0]==symbol) //Check the LHS
            {
                int j = 2;
                char temp_first[SIZE]={'\0'};
                while(productions[i][j]!='\0')
                {
                    calc_first(productions[i][j],temp_first);
                    for(int l=0;temp_first[l]!=0;l++) //Copy the first set to result
                        set_add(set,temp_first[l]);
                    if(is_in_set(temp_first,'#')) 
                    {
                        //epsilon in first set, we need to consider next NT
                        j++;
                    }
                    else
                    {   //if epsilon is already in the set, remove it since there is atleast
                        // one NT in RHS that doesn't derive epsilon
                        set_remove(set,'#');break;
                    }
                }
            }
        }
    }
}
//Function to find the follow sets
void calc_follow(char symbol,char *set)
{
    if(symbol=='\0') //check for NUL character
        return;
    if(!isupper(symbol)) //a terminal, first is itself
    {
        set_add(set,symbol);
        return;
    }
    if(symbol==StartSymbol)
    {
        set_add(set,'$'); //Add $ to the follow of start symbol
    }
    //Search for symbol in all productions
    for(int i=0;i<num_productions;i++)
    {
        for(int j=2;productions[i][j]!='\0';j++)
        {
            if(symbol==productions[i][j])
            {
               if(productions[i][j+1]!='\0') //Not the last NT
               {
                    //char temp[SIZE]={'\0'};
                    if(!isupper(productions[i][j+1])&&productions[i][j+1]!='#') //Terminal 
                    {
                        set_add(set,productions[i][j+1]);
                    }
                    else if(productions[i][j+1]!='#') //Non terminal
                    {
                        set_union(set,firstsets[get_index(productions[i][j+1])]);
                        if(is_in_set(firstsets[get_index(productions[i][j+1])],'#'))
                        {
                            if(productions[i][j+2]=='\0') //Last NT so Follow of RHS
                                calc_follow(productions[i][0],set);
                            calc_follow(productions[i][j+2],set);
                        }
                    }
               }
               else //Last NT
               {
                    if(productions[i][0]!=symbol) //Prevent infinite loops
                    {
                        calc_follow(productions[i][0],set);
                    }
               }
            }
        }
    }
}

int main()
{
    char temp[LENGTH];
    read_productions();
    //Compute & print the first sets of all non terminals
    for(int i=0;NonTerminals[i]!='\0';i++)
    {
        strcpy(temp,"");
        calc_first(NonTerminals[i],temp);
        printf("First(%c):",NonTerminals[i]);
        //Store first sets to be used when computing follow.
        strcpy(firstsets[get_index(NonTerminals[i])],temp);
        printset(temp);
    }
    //Compute & print the follow sets of all non terminals
    for(int i=0;NonTerminals[i]!='\0';i++)
    {
        strcpy(temp,"");
        calc_follow(NonTerminals[i],temp);
        set_remove(temp,'#'); //There are no epsilons in follow sets
        printf("Follow(%c):",NonTerminals[i]);
        printset(temp);
    }
}
