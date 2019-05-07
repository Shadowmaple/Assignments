# include <stdio.h>

int main()
{
    int sum = 0, n;
    scanf("%d", &n);
    do {
        int i = n % 10;
        n /= 10;
        sum += i;
    } while(n);

    printf("%d\n", sum);
    return 0;
}