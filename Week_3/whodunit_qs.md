# Questions

## What's `stdint.h`?

stdint.h is a header file for c that allows you to declair the exact number of bits used to store your integer (in binary).

## What's the point of using `uint8_t`, `uint32_t`, `int32_t`, and `uint16_t` in a program?

Different programs/machines/file-types may use different numbers of bits to store each data type.
having access to integers of different length allows our program to run on multiple systems, 
just by changing the memory allocation for a specific datatype.

## How many bytes is a `BYTE`, a `DWORD`, a `LONG`, and a `WORD`, respectively?

BYTE = 1 byte (8 bits),
DWORD = 4 bytes (32 bits),
LONG = 4 bytes (32 bits),
WORD = 2 bytes (16 bits)

## What (in ASCII, decimal, or hexadecimal) must the first two bytes of any BMP file be? Leading bytes used to identify file formats (with high probability) are generally called "magic numbers."

In hexidecimal: 0x4d42.

## What's the difference between `bfSize` and `biSize`?

bfSize is the total number of bits for the entire file.
biSize is the size n bytes of the info header itsself

## What does it mean if `biHeight` is negative?

the sign of the biHeight specifies the origin or 'first pixel' of the image.
positive means that the origin is the lower left, negitive means the upper left.

## What field in `BITMAPINFOHEADER` specifies the BMP's color depth (i.e., bits per pixel)?

biBitCount

## Why might `fopen` return `NULL` in `copy.c`?

If the pathname provided is invalid or the file cannot be opened.

## Why is the third argument to `fread` always `1` in our code?

becasue we would like to read 1 single unit of size (2nd param) at a time when copying the file

## What value does `copy.c` assign to `padding` if `bi.biWidth` is `3`?

two (bits)

## What does `fseek` do?

sets the offset , from either the beginning or end of the file for the file being streamed.
i.e. how many bytes into this file should i jump before doing anything?

## What is `SEEK_CUR`?

the current position, in the file, of the file pointer. 
