#include <stdio.h>

void main()
{
    int num1, num2, num3;
    scanf("%d%d%d", &num1, &num2, &num3);

    int max = (num1 > num2) ? num1 : num2;
    int min = (num1 < num2) ? num1 : num2;
    int middle = num3;
    if (max <= num3) {
        middle = max;
        max = num3;
    } else if (min >= num3){
        middle = min;
        min = num3;
    }

    printf("%d %d %d\n", min, middle, max);

}