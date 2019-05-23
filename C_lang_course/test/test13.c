# include <stdio.h>

int main()
{
    int i, j;
    double num = 1;
    double n;
    for (i=2; 1; i++) {
        n = 1 / (float)i;
        if (n < 0.0001)
            break;
        n = (i % 2) ? n:(-n);
        num += n;
    }
    printf("%.8f\n", num);
    return 0;
}
