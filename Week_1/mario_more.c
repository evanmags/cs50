#include <cs50.h>
#include <stdio.h>

void print_spaces(int num, int row);
void print_bricks(int num, int row);

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
        print_spaces(num, row);
        print_bricks(num, row);
        printf("  ");
        print_bricks(num, row);
        printf("\n");
    }
}

void print_spaces(int num, int row)
{
    for(int spaces = 1; spaces < num - row; spaces++)
    {
        printf(" ");
    }
}

void print_bricks(int num, int row)
{
    for(int bricks = 0; bricks <= row; bricks++)
    {
        printf("#");
    }
}