#include <cs50.h>
#include <crypt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define _XOPEN_SOURCE
#include <unistd.h>

int main(int argc, string argv[])
{
//     return if not valid hash
        if(argc != 2)
        {
           printf("Usage: ./crack hash\n");
           return 1;
        }
        else
        {
            string hash = argv[1];
            
            char salt[3];
            salt[0] = hash[0];
            salt[1] = hash[1];
            salt[2] = '\0';
            char alphabet[] = "\0abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
            int len = strlen(hash);
            char pass_attp[6] = "\0\0\0\0\0\0";
            for(int fiv = 0; fiv < 52; fiv++) //5th letter in array;
            {
                for(int fou = 0; fou < 52; fou++) //4th letter in array;
                {
                    for(int thr = 0; thr < 52; thr++) //3th letter in array;
                    {
                        for(int two = 0; two < 52; two++) //2nd letter in array;
                        {
                            for(int one = 0; one < 52; one++) //1st letter in array;
                            {
                                pass_attp[4] = alphabet[fiv];
                                pass_attp[3] = alphabet[fou];
                                pass_attp[2] = alphabet[thr];
                                pass_attp[1] = alphabet[two];
                                pass_attp[0] = alphabet[one];
                                
                                if(strcmp(hash, crypt(pass_attp, salt)) == 0)
                                {
                                    printf("%s\n", pass_attp);
                                    return 0;
                                }
                            }   
                        }   
                    }   
                }  
            } 
        }
    printf("Password cannot be found...");
    return 1;
}


// accept one and only one, hashed password if(argc != 2)
// if no hash return 1
// take frist two chars from hash, (salt)
// define salt as hash[0], hash[1], \0

// set initial password to "\0\0\0\0\0\0" (empty chars in memory)

// crypt takes in a char and salt
// loop thrugh alphabet of lowers and caps while incrementing initial pass.

// \0 => a => z => A => Z
// search looks like this:
//  - - - - - -
//  x - - - - -
//  x x - - - -
//  x x x - - -
//  x x x x - - 
//  x x x x x -
//  return

// print password when found.
// return 0 if password is found.

// lots of loops!

// // fake submit to see tests... there were none


// brian:51.xJagtPnb6s = TF
// bjbrown:50GApilQSG3E2 = UPenn
// emc:502sDZxA/ybHs = puppy
// greg:50C6B0oz0HWzo = FTW
// jana:50WUNAFdX/yjA = Yale
// lloyd:50n0AAUD.pL8g = lloyd
// malan:50CcfIk1QrPr6 = maybe
// natmelo:50JIIyhDORqMU = nope
// rob:51v3Nh6ZWGHOQ = ROFL
// veronica:61v1CDwwP95bY = hola
// walker:508ny6Rw0aRio = sean
// zamyla:50cI2vYkF0YU2 = LOL
