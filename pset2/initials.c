#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(void)
{
    string name = GetString();    
    
    if(name != NULL)
    {  
        printf("%c", toupper(name[0]));
        for(int i = 1, n = strlen(name); i < n; i++)
        {
            if(name[i] == ' ')
                printf("%c", toupper(name[i+1]));             
        }
        printf("\n");    
        
    }
}
