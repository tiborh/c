#include <stdbool.h>

#ifndef MAX_INPUT_WIDTH
#define MAX_INPUT_WIDTH 512
#endif

#ifndef TEXT_DELIM
#define TEXT_DELIM "\t"
#endif

#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED
/* ^^ these are the include guards */

/* Prototypes for the functions */
char* get_input();
char* get_string(int, char**,int);
int get_int(int, char**);
long get_long(int, char**);
long long get_longlong(int, char**);
float get_float(int, char**);
double get_double(int, char**);
/* legacy: */
/* process  argc argv style input and return the first argument as long integer */
long process_input(int, char**);
enum dat_type {integer, longint, longlong, floating, doublefloat, longdouble, string};
typedef enum dat_type DatType;
struct Input {
  int num_of_args;
  char** args;
  int nu_of_needed;
  DatType type_of_needed;
};
typedef struct Input myInput;
char* proc_input(myInput);
bool check_DataType(char*, DatType, int);
#endif
