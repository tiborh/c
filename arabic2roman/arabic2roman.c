#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <math.h>

#define DEBUG 0
#define TESTING 1
#define MAX_INPUT 3999
#define MAX_ROMAN_WIDTH 15

char *arabic2roman(int , char *);

int main(int argc, char **argv) {

#if TESTING
  if (tests())
    printf("\nERROR\n");
  else
    printf("\nSUCCESS\n");
#else
  int arabic = input_proc(argc,argv);
  char roman[MAX_ROMAN_WIDTH+1];
  arabic2roman(arabic,roman);	/* function gives value to 'roman' */
  printf("%s\n",roman);
#endif
}

int input_proc(int argc, char **argv) {
  int arabic = 0;
#if DEBUG
  printf("argc: %d\n",argc);
  if (argc > 1)
    printf("argv[1]: %s\n",argv[1]);
#endif

  if (argc > 1) {
    if (sscanf(argv[1],"%d",&arabic) == EOF) {
      printf("Unsuccessful read of argv[1]");
      exit(1);
    }
  } else {
    printf("A positive integer not greater than %d is needed as argument.\n",MAX_INPUT);
    exit(1);
  }

#if DEBUG
  printf("arabic: %d\n",arabic);
#endif

  return arabic;
} 

char *arabic2roman(int input, char *output) {
#define ROWS 4
#define COLS 2
  char roman[MAX_ROMAN_WIDTH+1] = {};
  const char conversion_table[ROWS][COLS] = {{'I','V'},
					     {'X','L'},
					     {'C','D'},
					     {'M','\0'}};
  int row=0,column=0;
  int digit = 0;
  int i = 0;
  if (input > MAX_INPUT) {
    printf("Value must be less than or equal to %d\n",MAX_INPUT);
    exit(1);
  }
  while (input != 0) {
    char temp_roman[MAX_ROMAN_WIDTH+1];
    temp_roman[0] = '\0';
    digit = input%10;
    switch(digit) {
    case 1:
    case 2:
    case 3:
      for (i = 0; i < digit; i++)
	strncat(temp_roman,&conversion_table[row][0],1);
      break;
    case 4:
      strncat(temp_roman,&conversion_table[row][0],1);
      strncat(temp_roman,&conversion_table[row][1],1);
      break;
    case 5:
      strncat(temp_roman,&conversion_table[row][1],1);
      break;
    case 6:
    case 7:
    case 8:
      strncat(temp_roman,&conversion_table[row][1],1);
      for (i = 0; i < digit-5; i++)
	strncat(temp_roman,&conversion_table[row][0],1);
      break;
    case 9:
      strncat(temp_roman,&conversion_table[row][0],1);
      strncat(temp_roman,&conversion_table[row+1][0],1);
      break;
    }

    str_prepend(roman,temp_roman);
    row++;
    input -= input%10;
    input /= 10;
  }
  
  strcpy(output,roman);
  return output;
}

int str_prepend(char *str_into, char *str_which) {
  char strtmp[MAX_ROMAN_WIDTH];

  strtmp[0]='\0';
  strcpy(strtmp,str_into);
  strcpy(str_into,str_which);
  strcat(str_into,strtmp);

  return 0;
}

int tests(void) {

  int result = 0;

#define NU_OF_TESTCASES 22

  typedef struct test_input_structure{
    char *output;
    int input;
  }test_input;

  test_input Test_Inputs[NU_OF_TESTCASES] = {{"I",1},
					     {"II",2},
					     {"IV",4},
					     {"V",5},
					     {"VIII",8},
					     {"IX",9},
					     {"X",10},
					     {"XIV",14},
					     {"XV",15},
					     {"L",50},
					     {"LXXVII",77},
					     {"C",100},
					     {"CDXLIV",444},
					     {"D",500},
					     {"DCCLXXXIX",789},
					     {"M",1000},
					     {"MI",1001},
					     {"MDLVI",1556},
					     {"MDCCCXXX",1830},
					     {"MMDCLXXXVII",2687},
					     {"MMM",3000},
					     {"MMMCMXCIX",3999}};
  //printf("Reading: %s, %d\n",Test_Inputs[0].output,Test_Inputs[0].input);

  int i = 0;
  for (i = 0; i < NU_OF_TESTCASES; i++)
    if (!testcase(Test_Inputs[i].output,Test_Inputs[i].input))
      result = 1;

    return result;
}

int testcase(char* expected_output, int input) {
  char testcase_input[MAX_ROMAN_WIDTH];
  arabic2roman(input,testcase_input);
  printf("%4d: %12s was expected, %12s was received:",input,expected_output,testcase_input);
  if (strcmp(expected_output,testcase_input)) {
    printf("\tNOK\n");
    return 0;
  }
  else {
    printf("\tOK\n");
    return 1;
  }
  
}
