#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>

const char* TEST_STRING = "Anything that can possibly go wrong, does.";
int increment;
int unit_size;
long long reserved = 0;
long long counter = 0;
char** saved_addresses = NULL;
clock_t start, end_allocate, end_free;

void signal_callback_handler(int);

void init_program()
{
  signal(SIGINT, signal_callback_handler);
  unit_size = strlen(TEST_STRING)*sizeof(char);
  increment = strlen(TEST_STRING);
  start = end_allocate = end_free = 0;
  if (NULL == saved_addresses)
    {
      if (NULL != (saved_addresses = malloc(increment * sizeof(char *))))
	{
	  reserved = increment;
	  //printf("First reserve: success (%d)\n",increment);
	}
      else
	{
	  puts("Initial reservation for saved_addresses has been unsuccessful. Exiting...");
	  exit(1);
	}
    }
}

void print_maxmem()
{
  long long string_memory_size = counter * unit_size;
  long long saved_memory_size = reserved * sizeof(char*);
  long long bytesize =  string_memory_size + saved_memory_size;
  const double convconst = 1024.0;
  double kbytesize = bytesize/convconst;
  double mbytesize = kbytesize/convconst;
  double gbytesize = mbytesize/convconst;

  printf("Maximum memory used was: %lld bytes (%4.2lf kbytes, %4.2lf mbytes, %4.2lf gigabytes)\n",bytesize,kbytesize,mbytesize,gbytesize);
  printf("Percentage of all used for saving memory addresses: %5.2lf\n",((double)saved_memory_size / bytesize) *100.0); 
}

void freemem()
{
  print_maxmem();
  printf("Starting to free memory with counter at %lld\n",counter);
  long long tenth = counter / 10;
  long long tenth_counter = tenth;
  int percentage = 1;
  puts("If you see this and nothing below for a long time,\n and the hard disk does not work like crazy,\n then the program is stuck.\n Press Cttl-C");
  for(long long i = 0; i < counter; i++)
    {
      free(*(saved_addresses + i));
      if (i == tenth_counter)
	{
	  printf("%3d%%\n",10 * percentage++);
	  tenth_counter += tenth;
	}
    }
  if (NULL != saved_addresses)
    free(saved_addresses);
  end_free = clock();
}

void end_program(int exit_value)
{
  printf("Allocation time: %5.2lfs\n",(double)(end_allocate - start) / CLOCKS_PER_SEC);
  printf("Memory free time: %5.2lfs\n",(double)(end_free - end_allocate) / CLOCKS_PER_SEC);
  printf("Total time: %5.2lfs\n",(double)(end_free - start) / CLOCKS_PER_SEC);
  puts("The end");
  exit(exit_value);
}

void signal_callback_handler(int signum)
{
   printf("Caught signal %d\n",signum);
   if (0 == end_allocate)
     end_allocate = clock();
   freemem();
   end_program(signum);
   //exit(signum);
}

int reserve_more(void)
{
  char** ptrbuffer = NULL;
  ptrbuffer = realloc(saved_addresses,(reserved + increment) * sizeof(char*));
  if (NULL == ptrbuffer)
    {
      printf("Saved_addresses cannot be increased higher than %lld.\n",reserved);
      end_allocate = clock();
      freemem();
      return 1;
    }
  else
    {
      reserved+=increment;
      saved_addresses = ptrbuffer;
    }
  return 0;
}

char* reserve_engine(void)
{
  char* return_string = malloc(unit_size+1);
  if (NULL != return_string)
    {
      saved_addresses[counter++] = return_string;
      if (counter >= reserved)
	if (1 == reserve_more())
	  return NULL;
      strcpy(return_string,TEST_STRING);
    } else
    {
      puts("No more free space to allocate.");
      end_allocate = clock();
      freemem();
      counter = 0;
    }

  return return_string;
}

int main(int argc, char** argv)
{
  init_program();
  char* test_string = "Starting string.";
  puts("Testing dynamic memory allocation.");
  start = clock();
  while(NULL != test_string)
    test_string = reserve_engine();
  end_program(0);
  return 0;
}
