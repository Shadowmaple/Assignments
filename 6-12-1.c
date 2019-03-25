//漏斗状

#include <stdio.h>
int main()
{
    int n;

    do {
        printf("请输入奇数：");
        scanf("%d", &n);
    } while (!(n % 2));
    
    for (int i=0; i<n/2; i++) {
        for (int j=0; j<i; j++) {
            putchar(' ');
        }
        for (int k=0; k<2*(n-i)-n; k++) {
            putchar('*');
        }
        putchar('\n');
    }
    for (int i=0; i<n/2+1; i++) {
        for (int j=0; j<(n/2)-i; j++) {
            putchar(' ');
        }
        for (int k=0; k<2*i+1; k++) {
            putchar('*');
        }
        putchar('\n');
    }
    return 0;
}