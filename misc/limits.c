#include <stdio.h>
#include <limits.h>
#include <float.h>

int main(int argc, char** argv)
{
  puts("Signed variables:");
  printf("Char limits: [%d, %d]\n", CHAR_MIN, CHAR_MAX);
  printf("Short limits: [%d, %d]\n", SHRT_MIN, SHRT_MAX);
  printf("Integer limits: [%d, %d]\n", INT_MIN, INT_MAX);
  printf("Long limits: [%ld, %ld]\n", LONG_MIN, LONG_MAX);
  printf("Long long limits: [%lld, %lld]\n\n", LLONG_MIN, LLONG_MAX);

  puts("Unsigned pieces (where only the upper limit is interesting):");
  printf("uchar upper limit: %u\n",UCHAR_MAX);
  printf("ushort upper limit: %u\n",USHRT_MAX);
  printf("unint upper limit: %u\n",UINT_MAX);
  printf("ulong upper limit: %lu\n",ULONG_MAX);
  printf("ulonglong upper limit: %llu (%e)\n\n",ULLONG_MAX,(double)ULLONG_MAX);

  puts("Floating point maxes:");
  printf("float radix (base): %d\n", FLT_RADIX);
  printf("float: %d mantissa digits\n", FLT_MANT_DIG);
  printf("float min/max: [%g, %g]\n", FLT_MIN, FLT_MAX);
  printf("double: %d mantissa digits\n", DBL_MANT_DIG);
  printf("double min/max: [%g, %g]\n", DBL_MIN, DBL_MAX);
  printf("long double: %d mantissa digits\n", LDBL_MANT_DIG);
  printf("long double min/max: [%Lg, %Lg]\n", LDBL_MIN, LDBL_MAX);

  return 0;
}
