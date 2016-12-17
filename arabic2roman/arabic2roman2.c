#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <math.h>

#define DEBUG 0
#define TESTING 0
#define MAX_INPUT 3999
#define MAX_ROMAN_WIDTH 15

char *arabic2roman(int , char *);

typedef struct test_input_structure{
  int input;
  char output[MAX_ROMAN_WIDTH+1];
}test_input;

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
#define LINEWIDTH 64
  int result = 0;

  char *filename = "arabic2roman_testinput.csv";

  int nu_of_testcases = count_lines(filename);
  if (nu_of_testcases == 0) {
    printf("No testcase has been found.\n");
    exit(1);
  }

  test_input *Test_Inputs;
  Test_Inputs = (test_input *) calloc (nu_of_testcases, sizeof(test_input));
  get_testcases(filename,nu_of_testcases,Test_Inputs);

  int i = 0;
  for (i = 0; i < nu_of_testcases; i++)
    if (!testcase(Test_Inputs[i].output,Test_Inputs[i].input))
      result = 1;

    return result;
}

int count_lines(char *inname) {

  int nu_of_lines = 0;

  FILE *fpt_infile;
  char str_tmp[LINEWIDTH];
  
  if((fpt_infile = fopen(inname,"r"))==(FILE *)NULL) {
    fprintf(stderr, "Cannot open file: %s.\n",inname);
    return 1;
  }

  while(fgets(str_tmp,LINEWIDTH,fpt_infile))
    nu_of_lines++;

  fclose(fpt_infile);

  return nu_of_lines;
}

int get_testcases(char *inname, int nu_of_testcases, test_input *the_tests) {
  FILE *fpt_infile;
  char str_tmp[LINEWIDTH];
  int i = 0;
  int test_input = 0;
  char test_output[MAX_ROMAN_WIDTH+1];

  if((fpt_infile = fopen(inname,"r"))==(FILE *)NULL) {
    fprintf(stderr, "Cannot open file: %s.\n",inname);
    return 1;
  }

  for(i = 0; i < nu_of_testcases; i++) {
    fgets(str_tmp,LINEWIDTH,fpt_infile);
    sscanf(str_tmp,"%d,%s",&test_input,test_output);
    //printf("%3d: %d, %s\n",i,test_input,test_output);
    the_tests[i].input = test_input;
    strncpy(the_tests[i].output,test_output,MAX_ROMAN_WIDTH);
  }

  fclose(fpt_infile);

  return 0;
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
