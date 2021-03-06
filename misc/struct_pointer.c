#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define STRLENGTH 64

struct Emplee {
  int id;
  char name[STRLENGTH];
  char position[STRLENGTH];
  char boss[STRLENGTH];
  long salary;
};
typedef struct Emplee employee;

employee* fill_struct(int, char*, char*, long);
void print_struct(employee*);

int main(int argc, char** argv)
{
  employee* test_emplee0 = fill_struct(123,"Savoy","Ruben",60000);
  print_struct(test_emplee0);

  employee* test_emplee1 = fill_struct(007,"Ruben","Ruth",500000);
  print_struct(test_emplee1);

  employee* test_emplee2 = fill_struct(001,"Ruth","God",2500000);
  print_struct(test_emplee2);

  return 0;
}

employee* fill_struct(int id, char* name, char* boss, long salary)
{
  employee* emplee2build = malloc(sizeof(employee));
  emplee2build->id = id;
  strcpy((*emplee2build).name,name); /* not such a nice looking solution */
  strcpy(emplee2build->boss,boss);
  emplee2build->salary = salary;

  return emplee2build;
}

void print_struct(employee* emplee2print)
{
  printf("id:\t%d\n",emplee2print->id);
  printf("name:\t%s\n",emplee2print->name);
  printf("boss:\t%s\n",emplee2print->boss);
  printf("salary:\t%ld\n",emplee2print->salary);
}
