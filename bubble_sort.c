#include <stdio.h>
int main()
{
    int a[8]={2,12,53,3,64,23,55,23};
    for (int i=0; i<8; i++) {
        for (int j=7; j>i; j--) {
            if (a[j]<a[i]) {
                int b = a[i];
                a[i] = a[j];
                a[j] = b;
            }
        }
    }
    for (int i=0; i<8; i++)
        printf("%d ", a[i]);
        
    putchar('\n');
    return 0;
}