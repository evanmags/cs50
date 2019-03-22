#include <stdio.h>
#include <cs50.h>

bool visa_test(long num);
bool amex_test(long num);
bool mc_test(long num);
bool luns_test(long card_num);

int main(void)
{
    long number = get_long("Number: ");
    
    if(luns_test(number)){
       if(mc_test(number))
        {
            printf("MASTERCARD\n");
        }
        else if(visa_test(number))
        {
            printf("VISA\n");
        }
        else if(amex_test(number))
        {
            printf("AMEX\n");
        }
        else
        {
            printf("INVALID\n");    
        }
    }
    else
    {
        printf("INVALID\n");    
    }
}

bool visa_test(long num)
{
    int testOne = num / 1000000000000;
    int testTwo = num / 1000000000000000;
    
    if(testOne == 4 || testTwo == 4)
    {
        return true;
    }
    
    return false;
}

bool amex_test(long num)
{
    int test = num / 10000000000000;
    
    if(test == 34 || test == 37)
    {
        return true;
    }
    
    return false;
}

bool mc_test(long num)
{
    int test = num / 100000000000000;
    
    if(test == 51 || test == 52 || test == 53 || test == 54 || test == 55)
    {
        return true;
    }
    
    return false;
}

bool luns_test(long card_num)
{
    int odd_sum = 0, even_sum = 0, digit, digit_hold, test, last;
    do
    {
        digit = card_num % 10;
        odd_sum += digit;
        
        card_num = (card_num - digit) / 10;
        
        digit = card_num % 10;
        digit_hold = digit * 2;
        
        if(digit_hold > 9)
        {
            last = digit_hold % 10;
            even_sum += last;
            last = (digit_hold - last) / 10;
            even_sum += last;
        }
        else
        {
            even_sum += digit_hold;
        }
        
        card_num = (card_num - digit) / 10;
    }
    while(card_num > 0);
    test = odd_sum + even_sum;
    if(test % 10 == 0)
    {
        return true;
    }
    return false;
}
