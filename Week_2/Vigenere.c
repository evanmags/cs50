#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int shift(char c);
bool check_alpha(string arg);
int wrap_letter(int letter, int base);

int main(int argc, string argv[])
{
//     check for correct number of arguments adn that arguments are alpha chars
    if(argc != 2 || !check_alpha(argv[1]))
    {
        printf("Usage: ./vigenere keyword\n");
        return 1;
    }
    else
    {
//         get string and define length
        string plaintext = get_string("paintext: ");
        int length = strlen(plaintext);
        // get length of arg for looping.
        int arglen = strlen(argv[1]);
        // placeholder value to avoid error, also allows the first arg to be a non alpha without issue.
        int key = 0;
        // counter for number of non alpha spaces in string.
        int skip = 0;
//         loop through string
        for(int i = 0; i < length; i++)
        {   
           //same as caesar
            int letter = plaintext[i];
            
            if(isupper(plaintext[i]))
            {   
                // take the first argument
                // take the current index fron the running loop and take out how manu skipped chars there have been.
                // modulo out the length of the argument 
                // result is the index of the letter to use in shift
                // 'shift' => a wrap function that gets the distance from a or A
                key = shift(argv[1][(i - skip) % arglen]);
                letter += key;
                letter = wrap_letter(letter, 65);
            }
            else if(islower(plaintext[i]))
            {
                key = shift(argv[1][(i - skip) % arglen]);
                letter += key;
                letter = wrap_letter(letter, 97);
            }
            else
            {
                skip ++;
            }
            plaintext[i] = (char) letter;
        }
        printf("ciphertext: %s\n", plaintext);
        return 0;
    }
}

int shift(char c)
{
    // same wrap as below but negates teh added in 'base'
    if(isupper(c))
    {
        return wrap_letter(c, 65) - 65;
    }
    else if(islower(c))
    {
        return wrap_letter(c, 97) - 97;
    }
    return c;
}

bool check_alpha(string arg)
{   
    // loop through to make sure argument is entirely aplha
    // return false if any case fails.
    int len = strlen(arg);
    for(int i = 0; i < len; i++)
    {
        if(!isalpha(arg[i]))
        {
            return false;
        }
    }
    return true;
}

int wrap_letter(int letter, int base)
{
    // same as caesar
    return ((letter - base) % (26)) + base;
}
