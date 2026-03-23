#include <stdio.h>

long long square(long long x)
{
    return (x * x);
}

int main(void)
{
    long long i = 0;
    long long value;
    do
    {
        i = (i + 1);
        value = square(i);
        if ((value > 2))
        {
            printf("%s\n", "big");
        }
        else
        {
            printf("%s\n", "small");
        }
        printf("%lld\n", value);
    }
    while (!((i == 3)));
    if ((i == 3))
    {
        printf("%s\n", "finished");
    }
    else
    {
        printf("%s\n", "unexpected");
    }
    return 0;
}
