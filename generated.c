#include <stdio.h>
#include <math.h>

long long square(long long x)
{
    return (x * x);
}

int main(void)
{
    long long i = 1;
    long long value;
    for (; (i <= 3); i = (i + 1))
    {
        value = square(i);
        printf("%s", "square = ");
        printf("%lld", value);
        printf("\n");
    }
    if (i == 4)
    {
        printf("%s", "finished");
        printf("\n");
    }
    else
    {
        printf("%s", "unexpected");
        printf("\n");
    }
    return 0;
    return 0;
}
