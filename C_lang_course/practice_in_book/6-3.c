# include <stdio.h>

int main()
{
    int sum = 0;
    for (int i=1; i<=10; i++) {
        int total = 1;
        for (int j=1; j<=i; j++)
            total *= j;
        sum += total;
    }

    printf("%d\n", sum);

    return 0;
}