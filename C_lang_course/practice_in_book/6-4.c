# include <stdio.h>

int main()
{
    int a, sum = 0, n;
    scanf("%d%d", &n, &a);

    int total = 0;
    for (int i=0; i<n; i++) {
        total = total * 10 + a;
        sum += total;
    }

    printf("%d\n", sum);

    return 0;
}