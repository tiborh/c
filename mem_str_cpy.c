#include <stdio.h>
#include <string.h>

void dump5(char *str);

int main()
{
    char s[5]={'s','a','\0','c','h'};

    char membuff[5]; 
    char strbuff[5];
    memset(membuff, 0, 5); // init both buffers to nulls
    memset(strbuff, 0, 5);

    strcpy(strbuff,s);
    memcpy(membuff,s,5);

    printf("original:\n\t");
    dump5(s);
    printf("memcpy:\n\t");
    dump5(membuff); // show what happened
    printf("strcpy:\n\t");
    dump5(strbuff);

    return 0;
}

void dump5(char *str)
{
    char *p = str;
    for (int n = 0; n < 5; ++n)
    {
        printf("%2.2x ", *p);
        ++p;
    }

    printf("\t");

    p = str;
    for (int n = 0; n < 5; ++n)
    {
        printf("%c", *p ? *p : ' ');
        ++p;
    }

    printf("\n");
}
