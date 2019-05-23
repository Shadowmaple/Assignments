#include<stdio.h>
#include<string.h>

void jssort(char *s)
{
    int i, j;
    char a[1000];
    int x;
    FILE *f, *out;

    for (i=0; i < strlen(s); i++) {
        if (i % 2 == 0) {
            a[i] = s[i];
            continue;
        }
        a[i] = s[i];
        for (j=1; i != j && j < strlen(a); j+=2) {
            if (s[i] > a[j]) {
                x = a[i];
                a[i] = a[j];
                a[j] = x;
            }
        }
    }
    a[i] = '\0';
    printf("%s\n", a);

    f = fopen("file1.txt", "w+");
    if (f == NULL)
        printf("error\n");
    fputs(a, f);
    fclose(f);

    out = fopen("file1.txt", "r+");
    fgets(a, strlen(a)+1, out);
    printf("%s\n", a);
    fclose(out);
}

int main()
{
    char s[1000];

    scanf("%s", s);
    jssort(s);

    return 0;
}
