# include <stdio.h>

int main()
{
    int i;
    int n;
    int n_max = 0, n_min = 0;
    for (i=0; 1; i++) {
        scanf("%d", &n);
        if (!n)
            break;
        else if (n > 0)
            n_max++;
        else
            n_min++;
    }
    printf("%d\n%d\n", n_max, n_min);

    return 0;
}
