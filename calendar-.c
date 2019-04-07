//万年历

#include <stdio.h>

int get_blank(int year)
{
    year--;
    int c = year / 100;
    int y = year - c * 100;
    int week = y + y / 4 + c / 4 - 2 * c + 26 * 14 / 10;
 //   while (week < 0)
   //     week += 7;
    week %= 7;
    return week;
}

int main()
{
    int day[12]={31,28,31,30,31,30,31,31,30,31,30,31};
    char week[] = " SUN MON TUE WED THU FRI STA ";
    int blank[12] = {0};
    int value[12][6][7] = {0};
    int year;
    
    scanf("%d", &year);
    if (year % 400 == 0 || (year%4==0 && year%100))
        day[1] = 29;

    blank[0] = get_blank(year);
    //月份
    for (int i=0, num=1; i<12; i++, num=1) {
        int flag = 0;
        //行数
        for (int j=0; j<6; j++) {
            int k = 0;
            //空白数
            if (j==0) {
                k = blank[i];
            }
            //列数
            for (; k<7; k++) {
                value[i][j][k] = num;
                //到达本月最后一天
                if (num == day[i]) {
                    flag = 1;
                    break;
                } else {
                    num++;
                }
            }
            if (flag) {    
                blank[i+1] = blank[i] + day[i] - j*7;
                if (blank[i+1] == 7)
                    blank[i+1] = 0;
                printf("%d\n", blank[i]);
                break;
            }
        }
        printf("\n*%d\n", value[0][0][0]);
        for (int x=0; x<6; x++) {
            for (int y=0; y<7; y++) {
                printf("%3d", value[i][x][y]);
            }
            putchar('\n');            //一个月7列
        }        num = 1;
        putchar('\n');
    }
//    value[0][0][0] = 0;
    if (blank[0])
        value[0][0][0] = 0;

    printf("\t\t-------%d年万历表--------\n", year);
    int month = 0;

    //一列四个月
    for (int i=0; i<4; i++) {
        //一个月6行
        for (int j=0; j<6; j++) {
            int m = month;
            for (int x=0; x<3; x++, m++) {
                //一个月7列
                for (int y=0; y<7; y++) {
                   if (value[m][j][y]==0)
                        printf("   ");
                    else                
                        printf("%3d", value[m][j][y]);
                }
                putchar('\t');
            }

            putchar('\n');
        }
        month += 3;
        putchar('\n');
    }
    
    return 0;
}