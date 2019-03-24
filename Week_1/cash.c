#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    float dollars;
    int coins = 0;
        
    // get a float that is equivelent to how much change is due
    do
    {
        dollars = get_float("How much change is due: ");
    }
    while(dollars < 0);

    // convert to cents and round off
    int cents = round(dollars * 100);
    
    // take out quarters
    coins += cents / 25;
    cents %= 25;
    
    // take out dimes
    coins += cents / 10;
    cents %= 10;
    
    // take out nickles
    coins += cents / 5;
    cents %= 5;
    
    // remainder is pennies
    coins += cents;
    
    // return the total number of coins
    printf("%i\n", coins);
}