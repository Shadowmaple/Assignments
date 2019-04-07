//严格以日历表的形式输出日历

#include <stdio.h>
int main()
{
    int day[12]={31,28,31,30,31,30,31,31,30,31,30,31};
    int total=2;
    puts("2019年日历表");
    printf("   ");
    for (int i=0; i<12; i++){
        for (int j=1; j<=day[i]; j++, total++) {
            printf("%2d ", j);
            if (total==7) {
                putchar('\n');
                total = 0;
            }
        }
        if (total != 1) putchar('\n');
        for (int n=1; n<total; n++) {
            printf("   ");
        }
    }
    putchar('\n');
    return 0;
}