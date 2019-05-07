# include <stdio.h>

int main()
{
    int total = 0;
    for (int i=1; i<=99; i += 2) {
        total += i * (i+1) * (i+2);
    }

    printf("%d\n", total);
    return 0;
}