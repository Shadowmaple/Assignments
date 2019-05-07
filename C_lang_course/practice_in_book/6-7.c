//水仙花数

# include <stdio.h>
# include <math.h>

int main()
{
    int count = 0;

    for (int i=100; i <= 999; i++) {
        int one_beat = i % 10;
        int ten_beat = (i % 100) / 10;
        int hunderd_beat = i / 100;
        int sum = pow(one_beat, 3) + pow(ten_beat, 3) + pow(hunderd_beat, 3);
        if (sum != i)
            continue;
        printf("%d\n", i);
        count++;
    }
    printf("%d个\n", count);
    return 0;
}