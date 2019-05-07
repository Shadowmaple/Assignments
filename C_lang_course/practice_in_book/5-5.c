#include <stdio.h>

int main()
{
    int month, year;
    int day[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    scanf("%d%d", &year, &month);
    if (month == 2) {
        if (year % 400 == 0 || year % 4 == 0 && year % 100)
            puts("29");
        else puts("28");
        return 0;
    }

    switch (month) {
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12: puts("31"); break;
        default: puts("30");
    }

    return 0;
}