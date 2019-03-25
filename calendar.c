#include <stdio.h>
int main()
{
    int day[12]={31,28,31,30,31,30,31,31,30,31,30,31};
    int total=1;
    printf("2019年日历表\n");
    for (int i=0; i<12; i++) {
        printf("%d月\n", i+1);
        for (int j=1; j<=day[i]; j++) {
            printf("%2d ", j);
            if (!(j % 7))
                putchar('\n');
        }
        putchar('\n');
    }

    return 0;
}