#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int n;
    do
    {
        printf("Please enter a positive integer:");
        n = GetInt();
    }
    while(n>23 || n<1);
    
    int bricks = 2;
    int spaces;
    for(int i = 0; i<n; i++) {
        spaces = (n+1)-bricks;
        
        for(int s = 0; s < spaces; s++)
            printf(" ");
            
        
        for(int b = 0; b < bricks; b++)
            printf("#");
            
        printf("\n");
        bricks++;
    }
}
