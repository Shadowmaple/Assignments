# include <stdio.h>

int main()
{
    int i, j;
    int num[3][4];
    int max_num = 0;
    int max_x = 0, max_y = 0;
    for (i=0; i < 3; i++) {
        for (j=0; j < 4; j++) {
            scanf("%d", &num[i][j]);
            if (max_num < num[i][j]) {
                max_num = num[i][j];
                max_x = i;
                max_y = j;
            }
        }
    }
    printf("%d %d %d\n", max_num, max_x, max_y);
    return 0;
}
