# include <stdio.h>

int main()
{
    int i, j;
    int sum;
    int n[30];
    float m[6];
    for (i=0, j=2; i < 30; i++, j+=2)
        n[i] = j;

    for (i=0, j=0; i < 30; i += 5) {
        sum = n[i] + n[i+1] + n[i+2] + n[i+3] + n[i+4];
        m[j++] = sum / 5;
        printf("%.2f ", m[j-1]);
    }
    putchar('\n');
    return 0;
}
