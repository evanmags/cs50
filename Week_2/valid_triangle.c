#include <stdio.h>
#include <stdbool.h>

bool valid_triangle(float a, float b, float c);

int main(void)
{
  printf("What is the lenght of side a: ");
  float a = get_float();

  printf("What is the lenght of side b: ");
  float b = get_float();

  printf("What is the lenght of side c: ");
  float c = get_float();

  bool triangle  = valid_triangle(a, b, c);

  if(triangle)
  {
    printf("This is a valid triangle");
  }
  else
  {
    printf("This is not a vlaid triangle.");
  }
}

bool valid_triangle(float a, float b, float c)
{
  if( a < 0 || b < 0 || c < 0)
  {
    return false;
  }
  if(  a + b > c
    || b + c > a
    || c + a > b)
  {
    return true;
  }
  else
  {
    return false;
  }
  
}