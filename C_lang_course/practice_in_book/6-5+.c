#include <stdio.h>

int main()
{
    float total = 1, term;
    
    for (int n=2; n <= 100; n += 2) {
        term = (float) (n * n) / ((n - 1)*(n + 1));
        total *= term;
    }

    printf("%f\n", total * 2);
    return 0;
}