#include<stdio.h>

int main()
{
    char a[N+1], b[N+1], c[N+1];
    
    printf("a=");
    scanf("%s", a);
    printf("b=");
    scanf("%s", b);
    memset(c, ' ', N+2);

    multiply_number(a, b, c);
    printf("a*b=%s\n", c);

    return 0;
}