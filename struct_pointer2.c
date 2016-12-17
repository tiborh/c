#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define STRLENGTH 64
#define HEADCOUNT 10

struct Emplee {
  int id;
  char name[STRLENGTH];
  char position[STRLENGTH];
  char boss[STRLENGTH];
  long salary;
};
typedef struct Emplee employee;

struct Staff {
  employee* emplees[HEADCOUNT];
  int nMplees;
};
typedef struct Staff staff;


employee* fill_emplee_data(int, char*, char*, long);
void print_emplee_data(employee*);
int add2staff(staff*, int, char*, char*, long);
void print_staff_data(staff*);
void print_member_added(int);
void free_staff(staff*);

int main(int argc, char** argv)
{
  staff* test_staff = malloc(sizeof(staff));
  test_staff->nMplees = 0;


  if (add2staff(test_staff,123,"Savoy","Ruben",60000))
    printf("Member %d has been added\n",test_staff->nMplees);

  if(add2staff(test_staff,007,"Ruben","Ruth",500000))
    printf("Member %d has been added\n",test_staff->nMplees);

  if(add2staff(test_staff,001,"Ruth","God",2500000))
    printf("Member %d has been added\n",test_staff->nMplees);

  print_staff_data(test_staff);
  printf("Pointer address to staff: %p\n",test_staff);
  printf("Size of the structure: %ul\n",sizeof(*test_staff));

  free_staff(test_staff);
  puts("test_staff is free.");

  return 0;
}

employee* fill_emplee_data(int id, char* name, char* boss, long salary)
{
  employee* emplee2build = malloc(sizeof(employee));
  emplee2build->id = id;
  strcpy((*emplee2build).name,name); /* not such a nice looking solution */
  strcpy(emplee2build->boss,boss);
  emplee2build->salary = salary;

  return emplee2build;
}

void print_emplee_data(employee* emplee2print)
{
  printf("id:\t%d\n",emplee2print->id);
  printf("name:\t%s\n",emplee2print->name);
  printf("boss:\t%s\n",emplee2print->boss);
  printf("salary:\t%ld\n",emplee2print->salary);
}

int add2staff(staff* theStaff,int id, char* name, char* boss, long salary)
{
  if (theStaff->nMplees == HEADCOUNT) 
    {
      fprintf(stderr,"staff is full, no more can be employed\n");
      return 0;
    }

  theStaff->emplees[theStaff->nMplees++] = fill_emplee_data(id,name,boss,salary);
  
  return 1;
}

void print_staff_data(staff* staff2print)
{
  int staff_size = staff2print->nMplees;
  for (int i = 0; i < staff_size; i++)
    print_emplee_data(staff2print->emplees[i]);
}

void free_staff(staff* staff2free)
{
  int staff_size = staff2free->nMplees;
  for (int i = 0; i < staff_size; i++)
    free(staff2free->emplees[i]);
  free(staff2free);
}
