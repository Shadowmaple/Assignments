# include <stdio.h>

int main()
{
    int s, p, w, d, f;

    scanf("%d%d%d", &p, &w, &s);

    switch (s / 250) {
        case 0: d = 0; break;
        case 1: d = 2; break;
        case 2:
        case 3: d = 5; break;
        case 4:
        case 5:
        case 6:
        case 7: d = 8; break;
        case 8:
        case 9:
        case 10:
        case 11: d = 10; break;
        default: d = 15;
    }

    f = p * w * s * (1 - d / 100);
    printf("%d\n", f);

    return 0;
}