#include <stdio.h>
#include <string.h>

struct TestStruct {
  char* name;
  int year_of_birth;
  char job[63];
  char address[127];
};

void printstruct(struct TestStruct* instruct)
{
  puts(instruct->name);
  printf("%d\n",instruct->year_of_birth);
  puts(instruct->job);
  puts(instruct->address);
}

void printdata(const void* source, size_t n)
{
  /* print data byte by byte */

  const char* sourcep = (const char*) source;

  while (n--)
    printf("%x ",*sourcep++);
  puts("");
}

void printdata_b(const void* source, size_t n)
{
  /* print data byte by byte */

  const char* sourcep = (const char*) source;

  while (n--)
    printf("%c ",*sourcep++);
  puts("");
}


int main(int argc, char** argv)
{
  float x = 1.0;
  printf("%f: ",x);
  printdata(&x,sizeof(float));
  puts("");

  x = 100.0;
  printf("%f: ",x);
  printdata(&x,sizeof(float));
  puts("");

  int year = 1980;
  printf("%d: ",year);
  printdata(&year,sizeof(int));
  puts("");

  long long j = 1546546546154;
  printf("%lld: ",j);
  printdata(&j,sizeof(long long));
  puts("");
  
  char* name = "Sally Dowson";
  printf("pointer to name: %p\n",name);
  puts(name);
  printdata(name,strlen(name)*sizeof(char));
  puts("");

  struct TestStruct Sally = {name,year,"Assistant","38 Crescent Row, Dublin"};
  printstruct(&Sally);
  printdata(&Sally,sizeof(struct TestStruct));
  puts("");
  printdata_b(&Sally,sizeof(struct TestStruct));
  puts("");

  return 0;
}
