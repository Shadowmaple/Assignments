# include <stdio.h>

void count_num(float *n, float *ava, int *num, float *sum)
{
    int i;
    *ava = *sum / 10;
    for (i=0; i < 10; i++) {
        if (n[i] > *ava) {
            (*num)++;
        }
    }
}

int main()
{
    int i;
    float n[10];
    float ava, sum;
    int num = 0;
    for (i=0; i < 10; i++) {
        scanf("%f", &n[i]);
        sum += n[i];
    }

    count_num(n, &ava, &num, &sum);
    printf("%.3f %d\n", ava, num);

    return 0;
}
