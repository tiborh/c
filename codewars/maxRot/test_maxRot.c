#include <stdio.h>
#include <stdlib.h>
#include <criterion/criterion.h>

long long maxRot(long long n);

void dotest(long long n, long long exp)
{
    long long act = maxRot(n);
    if(act != exp)
        printf("Error. Expected %lld but got %lld\n", exp, act);
    cr_assert_eq(act, exp, "");
}

Test(maxRot, ShouldPassAllTheTestsProvided) {
  dotest(1, 1);
  dotest(21, 21);
  dotest(15, 51);
  dotest(108, 108);
  dotest(150, 501);
  dotest(56789,68957);
  dotest(38458215, 85821534);
  dotest(195881031, 988103115);
  dotest(896219342, 962193428);
  dotest(69418307, 94183076);
}
