#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int num;
        
    do
    {
        num = get_int("Height: ");
    }
    while(num < 1 || num > 8);
    
    for(int row = 0; row < num; row++)
    {
        for(int spaces = 1; spaces < num - row; spaces++)
        {
            printf(" ");
        }
        for(int bricks = 0; bricks <= row; bricks++)
        {
            printf("#");
        }
        printf("\n");
    }
}

// psudocode for problem
// declare integer NUM.
// first get user input for how tall/wide the pyramid should be.
// set NUM equal to input
// while NUM is not between 1 and 8 ask for integer.
// for integer ROW from 0 up to and not including NUM, do the following:
//   make a string of spaces equal to NUM - ROW
//   make a string of # equal to ROW
//   print the string "(spaces)(#'s)"
