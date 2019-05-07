# include <stdio.h>

int main()
{
    int x;
    scanf("%d", &x);
    if (x > 0)
        puts("1");
    else if (x == 0)
        puts("0");
    else
        puts("-1");
    
    return 0;
}