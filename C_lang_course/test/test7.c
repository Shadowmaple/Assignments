# include <stdio.h>
# include <math.h>

int main()
{
    int i, j;
    float x = 3.1415 / 4;
    float f = 0;

    for (i=0; 1; i++) {
        f = cos(x) - x;
    //    printf("f^^^%f\n", f);

        if (f <= 0.001 && f >= -0.001)
            break;

        x = x - (cos(x) - x) / (-sin(x) - 1);
  //          printf("x=%f\n", x);

    }
    printf("%f\n", x);

    return 0;
}
