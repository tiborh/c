#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const long long MAXNUM = 536000000;
const char* test_string = "Anything that can possibly go wrong, does.";
long long maxnum;
//char** saved_addresses;

/*
void freemem(long long counter)
{
  printf("Starting to free memory at counter %lld (out of %lld, %4.2f%%)\n",counter,MAXNUM,((float)counter/(float)MAXNUM)*100);
  for(long long i = 0; i < counter; i++)
    free(saved_addresses[i]);
}
*/

void print_maxmem(long long bytesize)
{
  const double convconst = 1024.0;
  double kbytesize = bytesize/convconst;
  double mbytesize = kbytesize/convconst;
  double gbytesize = mbytesize/convconst;

  printf("Maximum memory used was: %lld bytes (%4.2lf kbytes, %4.2lf mbytes, %4.2lf gigabytes)\n",bytesize,kbytesize,mbytesize,gbytesize);
}

char* leaky(int freer)
{
  //saved_addresses = malloc(MAXNUM * sizeof(char*));
  /*
  if (NULL == saved_addresses)
    {
      puts("Cannot allocate enough space for 'saved_addresses'. Exiting...");
      exit(1);
    }
  */
  static long long counter = 0;
  char* return_string = NULL;
  int unit_size = strlen(test_string)*sizeof(char);

  if(1 == freer)
    {
      //freemem(counter);
      char* done = "Done.";
      print_maxmem(counter*unit_size);
      counter = 0;
      return_string = malloc(strlen(done)*sizeof(char)+1);
      strcpy(return_string,done);
      return return_string;
    }

  return_string = malloc(unit_size);
  if (NULL != return_string)
    {
      //saved_addresses[counter++] = return_string;
      counter++;
      strcpy(return_string,test_string);
    }
  else
    {
      puts("No more free space to allocate.");
      //freemem(counter);
      maxnum = counter;
      print_maxmem(counter*unit_size);
      counter = 0;
    }

  return return_string;
}

int main(int argc, char** argv)
{
  maxnum = MAXNUM;
  char* leaky_string = NULL;
  puts("Testing dynamic memory allocation.");
  for(long long i = 0; i < maxnum; i++)
    leaky_string = leaky(0);
  if (NULL != leaky_string)
    {
      puts(leaky_string);
      leaky_string = leaky(1);
      puts(leaky_string);
      free(leaky_string);
    }
  else
    puts("The end");
  return 0;
}
