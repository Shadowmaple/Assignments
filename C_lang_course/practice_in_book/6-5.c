# include <stdio.h>

int main()
{
    float total = 1;
    int i=2, j=1;
    int flag_i = 1, flag_j = 1;
    int k = 0;

    while(k < 100) {
        total *= (float) i / j;
        if (flag_i == 2) {
            flag_i = 1;
            i += 2;
        } else 
            flag_i++;
        
        if (flag_j == 2 || j == 1) {
            flag_j = 1;
            j += 2;
        } else
            flag_j++;

        k++;
    }

    printf("%f\n", total * 2);

    return 0;
}