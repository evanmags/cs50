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
            // can pass but not be ne of these three card companies
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
    // visas can be 13 or 16 numbers and always start with 4, if after dividing by 1e13 or 1e16 and removing float portions i get 4, then it is a valid number.
    int testOne = num / 1000000000000;
    int testTwo = num / 1000000000000000;
    
    if(testOne == 4 || testTwo == 4)
    {
        return true;
    }
    
    return false;
}

bool amex_test(long num)
{   // if remainder after dividing bu 1e15 is 34 or 37 it is valid
    int test = num / 10000000000000;
    
    if(test == 34 || test == 37)
    {
        return true;
    }
    
    return false;
}

bool mc_test(long num)
{   // if after dividing bu 1e16 remainder is 51, 52, 53, 54, or 55 test passes
    int test = num / 100000000000000;
    
    if(test == 51 || test == 52 || test == 53 || test == 54 || test == 55)
    {
        return true;
    }
    
    return false;
}

bool luns_test(long card_num)
{
    // takes in a card number
    int odd_sum = 0, even_sum = 0, digit, digit_hold, test, last;
    do
    {
        // pull out last digit, any 2+ digit number will leave last by %
        digit = card_num % 10;
        // all odd index digits from left to right get addded together
        odd_sum += digit;
        
        // remove last digit
        card_num = (card_num - digit) / 10;

        // pull new to last digit
        digit = card_num % 10;
        // all even index digits are doubled then all of their digits are added together.
        digit_hold = digit * 2;

        // if digit became 2 after doubling, add per the same opperation as above.
        if(digit_hold > 9)
        {
            last = digit_hold % 10;
            even_sum += last;
            last = (digit_hold - last) / 10;
            even_sum += last;
        }
        else
        {
            // if digit did not 'overflow' add to even digits
            even_sum += digit_hold;
        }
        
        // remove last digit
        card_num = (card_num - digit) / 10;
    } // loop until the card number 'disapears'
    while(card_num > 0);

    // add evens and odds together
    test = odd_sum + even_sum;

    // if sum is multiple of 10 it is a valid number
    if(test % 10 == 0)
    {
        return true;
    }
    return false;
}