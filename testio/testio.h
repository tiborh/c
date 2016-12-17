#ifndef HEADER_28028B6479FBC0ED
#define HEADER_28028B6479FBC0ED

#ifndef ROWS
#define MAXLINE 1024
#endif

#ifndef MAXNUM
#define MAXNUM 1024
#endif

#ifndef COLS
#define COLS 5
#endif

#ifndef ROWS
#define ROWS 7
#endif

#ifndef MAXDATW
#define MAXDATW (MAXLINE/COLS-3)
#endif

#ifndef DATSEP
#define DATSEP ','
#endif

FILE* open_file(char*,char*);
void close_file(FILE*,char*);
void print_int_arr(int*);
int writer(char*);
int processor(char*);

#endif // header guard
