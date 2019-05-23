# include <stdio.h>
# include <string.h>

int main()
{
    int i, j;
    int num[4] = {0};
    int k;

    for (i=0; 1; i++) {
        scanf("%d", &k);
        if (k == -1)
            break;
        switch (k)
        {
            case (1): num[0]++; break;
            case (2): num[1]++; break;
            case (3): num[2]++; break;
            case (4): num[3]++; break;
        }
    }
    printf("1:%d 2:%d 3:%d 4:%d\n", num[0], num[1], num[2], num[3]);

    return 0;
}
