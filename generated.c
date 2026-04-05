#include <stdio.h>
#include <math.h>

long long countPairs(long long rows, long long cols);

long long countPairs(long long rows, long long cols)
{
    long long i = 1;
    long long j;
    long long total = 0;
    for (; (i <= rows); i = (i + 1))
    {
        j = 1;
        for (; (j <= cols); j = (j + 1))
        {
            total = (total + 1);
        }
    }
    return total;
}

int main(void)
{
    long long result;
    result = countPairs(2, 3);
    printf("%s", "pairs = ");
    printf("%lld", result);
    printf("\n");
    return 0;
    return 0;
}
