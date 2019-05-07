#include <stdio.h>

int main()
{
    int num;
    scanf("%d", &num);
    
    if (num > 0)
        puts("正数");
    else if (num < 0)
        puts("负数");

    if (num % 2)
        puts("奇数");
    else
        puts("偶数");

    return 0;
}