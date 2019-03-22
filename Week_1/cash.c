#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    float dollars;
    int coins = 0;
        
    do
    {
         dollars = get_float("How much change is due: ");
    }
    while(dollars < 0);
    
    int cents = round(dollars * 100);
    
    coins += cents / 25;
    cents %= 25;
    
    coins += cents / 10;
    cents %= 10;
    
    coins += cents / 5;
    cents %= 5;
    
    coins += cents;
    
    printf("%i\n", coins);
}