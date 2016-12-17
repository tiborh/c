#include <stdio.h>

void* memcpy(void* target, const void* source, size_t n)
{
  /* copy an object to another */

  char* targetp = (char*) target;
  const char* sourcep = (const char*) source;

  while (n--)
    *targetp++ = *sourcep++;

  return target;
}

int main(int argc, char** argv)
{
  float x = 1.0, y = 2.0;
  printf("x == %f, y == %f\n",x,y);
  memcpy(&x,&y,sizeof(float));
  printf("x == %f, y == %f\n",x,y);
  return 0;
}
