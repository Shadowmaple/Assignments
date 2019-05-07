//此题踩了很多坑

# include <stdio.h>
# include <math.h>
# include <stdlib.h>

/*
//阶乘
int factorial(int k)
{
    int total = 1;
    for (int i=1; i <= k; i++) {
        total *= i;
    }
    return total;
}
*/

int main()
{
    int k = 2, flag = 1;
    float x;
    scanf("%f", &x);
    float result = x, term = x;

    while (1) {
        //int num = factorial(2 * k -1);
        //term = pow(-1, k+1) * pow(x, 2*k-1) / num;
        //只能累乘，若一项一项计算，则阶乘num会溢出

        term = -term * x * x / ((2*k-1) * (2*k-2));
        if (fabs(term) < pow(10, -5))
            break;
        result += term;
        //printf("%f %f\n", term, result);
        k++;
    }

    printf("sin(%f)=%f %d项\n", x, result, --k);
    return 0;
}