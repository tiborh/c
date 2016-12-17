#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <cs50.h>
#include <libgen.h>
#include <string.h>
#include <ctype.h>

// grid's dimensions
#define DIMENSION 4

// maximum number of words in any dictionary
#define WORDS 172806

// maximum number of letters in any word
#define LETTERS 29

// default dictionary
// http://www.becomeawordgameexpert.com/wordlists.htm
#define DICTIONARY "words"

// for logging
FILE* log;

// grid
char grid[DIMENSION][DIMENSION];

// flags with which we can mark grid's letters while searching for words
bool marks[DIMENSION][DIMENSION];

// defines a word as having an array of letters plus a flag
// indicating whether word has been found on grid
typedef struct
{
    bool found;
    char letters[LETTERS + 1];
}
word;

// defines a dictionary as having a size and an array of words
struct
{
    int size;
    word words[WORDS];
}
dictionary;

bool load(string s);

int main(int argc, char **argv) {

    // determine path to dictionary
    string directory = dirname(argv[0]);
    char path[strlen(directory) + 1 + strlen(DICTIONARY) + 1];
    sprintf(path, "%s/%s", directory, DICTIONARY);

    // load dictionary
    if (!load(path))
    {
        printf("Could not open dictionary.\n");
        return 1;
    }

  FILE *outfile;
  char myfile[] = "outfile.txt";
  if ((outfile = fopen(myfile,"w")) == NULL) {
    printf("Cannot open %s for writing\n",myfile);
    exit(1);
  }
  fprintf(outfile,"Dictionary size: %d\n",dictionary.size);
  for (int i = 0; i < dictionary.size; i++) {
    fprintf(outfile,"%s\n",dictionary.words[i].letters);
  }
  fputc('\n',outfile);
  fclose(outfile);


  return 0;
}

/**
 * Loads words from dictionary with given filename, s, into a global array.
 */
bool load(string s)
{
    // open dictionary
    FILE* file = fopen(s, "r");
    if (file == NULL)
        return false;

    // initialize dictionary's size
    dictionary.size = 0;

    // load words from dictionary
    char buffer[LETTERS + 2];
    while (fgets(buffer, LETTERS + 2, file))
    {
        // overwrite \n with \0
        buffer[strlen(buffer) - 1] = '\0';

        // capitalize word
        for (int i = 0, n = strlen(buffer); i < n; i++)
            buffer[i] = toupper(buffer[i]);

        // ignore SCRAMBLE
        if (strcmp(buffer, "SCRAMBLE") == 0) 
            continue;

        // copy word into dictionary
        dictionary.words[dictionary.size].found = false;
        strncpy(dictionary.words[dictionary.size].letters, buffer, LETTERS + 1);
        dictionary.size++;
    }

    // success!
    return true;
}
