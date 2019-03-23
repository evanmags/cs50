#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

bool arg_is_digits(string arg);
int wrap_letter(int letter, int base);
    
int main(int argc, string argv[])
{
    
    if(argc != 2 || !arg_is_digits(argv[1]))
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    else
    {
        int key = atoi(argv[1]);
        
        string plaintext = get_string("paintext: ");
        int length = strlen(plaintext);
        
        for(int i = 0; i < length; i++)
        {   
            int letter = plaintext[i];
            
            if(isupper(plaintext[i]))
            {
                letter += key;
                letter = wrap_letter(letter, 65);
            }
            else if(islower(plaintext[i]))
            {
                letter += key;
                letter = wrap_letter(letter, 97);
            }
            plaintext[i] = (char) letter;
        }
        printf("ciphertext: %s\n", plaintext);
        return 0;
    }
}

bool arg_is_digits(string arg)
{
    for(int i = 0; i < strlen(arg); i++){
        if(!isdigit(arg[i]))
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
