#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    float n;
    int cents;
    int numberOfCoins = 0;
    do
    {
        printf("Please enter a positive amount: ");
        n = GetFloat();
        n = n*100;
        cents = (int)round(n);
       
    }
    while(n<0); 
    
    while(cents>0)
    {
        if(cents % 25 >= 0 && cents/25>0)
        {
            numberOfCoins++;
            cents -= 25;
        }
        else if(cents % 10 >= 0 && cents/10>0)
        {
            numberOfCoins++;
            cents -= 10;
        }
        else if(cents % 5 >= 0 && cents/5>0)
        {
            numberOfCoins++;
            cents -= 5;
        }
        else 
        {
            numberOfCoins += cents;
            cents = 0;   
        }    
    }
    printf("%d\n", numberOfCoins);
}
