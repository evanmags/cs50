#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

bool arg_is_digits(string arg);
int wrap_letter(int letter, int base);
    
int main(int argc, string argv[])
{
    // if there are not exactly 2 args OR args are not digits, return error
    if(argc != 2 || !arg_is_digits(argv[1]))
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    else
    {
        // convert string representation of number to integer
        int key = atoi(argv[1]);
        
        // get the text to be encoded
        string plaintext = get_string("paintext: ");
        // get length of string for looping
        int length = strlen(plaintext);
        
        for(int i = 0; i < length; i++)
        {   
            // select individual letter for ciphering
            int letter = plaintext[i];
            
            // check case of letter
            if(isupper(plaintext[i]))
            {
                // add the cypher key to the letter
                letter += key;
                letter = wrap_letter(letter, 65);
            }
            else if(islower(plaintext[i]))
            {
                letter += key;
                letter = wrap_letter(letter, 97);
            }

            //convert letter from int to char and replace the origional with it.
            plaintext[i] = (char) letter;
        }
        printf("ciphertext: %s\n", plaintext);
        return 0;
    }
}

bool arg_is_digits(string arg)
{
    // loop through string of arg, check that every char is a digit not alpha or symb
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
    // subtract integer version of a or A
    // modulo out an alphabet to remove overflow and get distance from a or A
    // add back in a or A
    return ((letter - base) % (26)) + base;
}
