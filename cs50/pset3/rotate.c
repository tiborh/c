#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// grid's dimensions
#define DIMENSION 4

// grid
char grid[DIMENSION][DIMENSION];

void initialize(void);
void draw(void);
void scramble(void);

int main(int argc, char **argv) {

  // initialize the grid
  initialize();
  draw();
  if (argc > 1)
    if (strcmp(argv[1],"scramble") == 0) {
      scramble();
      draw();
    }

  return 0;
}

/**
 * Initializes grid with letters.
 */
void initialize(void)
{
    // http://en.wikipedia.org/wiki/Letter_frequency
    float frequencies[] = {
     8.167,  // a
     1.492,  // b
     2.782,  // c
     4.253,  // d
     12.702, // e
     2.228,  // f
     2.015,  // g
     6.094,  // h
     6.966,  // i
     0.153,  // j
     0.747,  // k
     4.025,  // l
     2.406,  // m
     6.749,  // n
     7.507,  // o
     1.929,  // p
     0.095,  // q
     5.987,  // r
     6.327,  // s
     9.056,  // t
     2.758,  // u
     1.037,  // v
     2.365,  // w
     0.150,  // x
     1.974,  // y
     0.074   // z
    };
    int n = sizeof(frequencies) / sizeof(float);

    // iterate over grid
    for (int row = 0; row < DIMENSION; row++)
    {
        for (int col = 0; col < DIMENSION; col++)
        {   
            // generate pseudorandom double in [0, 1]
            double d = rand() / (double) RAND_MAX;

            // map d onto range of frequencies
            for (int k = 0; k < n; k++)
            {
                d -= frequencies[k] / 100;
                if (d < 0.0 || k == n - 1)
                {
                    grid[row][col] = 'A' + k;
                    break;
                }
            }
        }
    }
}

/** 
 * Prints the grid in its current state.
 */
void draw(void)
{
  putchar('\n');
  for (int i = 0; i < DIMENSION; i++) {
    putchar(' ');
    for (int j = 0; j < DIMENSION; j++) {
      printf(" %c",grid[i][j]);
    }
    printf("\n");
  }
  putchar('\n');
}

void scramble(void)
{
    // TODO
  char shadow_grid[DIMENSION][DIMENSION];
  int i,j;

  for (i = 0; i < DIMENSION; i++)
    for (j = 0; j < DIMENSION; j++)
      shadow_grid[i][j] = grid[i][j];

  for (i = 0; i < DIMENSION; i++)
    for (j = 0; j < DIMENSION; j++)
      grid[j][DIMENSION-1-i] = shadow_grid[i][j];
}
