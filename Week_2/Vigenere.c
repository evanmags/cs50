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
//         get string adn define length
        string plaintext = get_string("paintext: ");
        int length = strlen(plaintext);
//         get length of key.
        int arglen = strlen(argv[1]);
        int key = 0;
        int skip = 0;
//         loop through string
        for(int i = 0; i < length; i++)
        {   
           
            int letter = plaintext[i];
            
            if(isupper(plaintext[i]))
            {   
                printf("%c", plaintext[i]);
                key = shift(argv[1][(i-skip) % arglen]);
                letter += key;
                letter = wrap_letter(letter, 65);
            }
            else if(islower(plaintext[i]))
            {
                printf("%c", plaintext[i]);
                key = shift(argv[1][(i-skip) % arglen]);
                letter += key;
                letter = wrap_letter(letter, 97);
            }
            else
            {
                skip++;
            }
            plaintext[i] = (char) letter;
        }
        printf("ciphertext: %s\n", plaintext);
        return 0;
    }
}

int shift(char c)
{
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
    return ((letter - base) % (26)) + base;
}
