#include <stdio.h>
#include <string.h>

#define N 20

int flag = 0;

void minus_number(char a[], char b[], char c[])
{
    int i=strlen(a)-1, j=strlen(b)-1, k=N;
    
    
}

void swap(char a[], char b[])
{
    char x[N+1];
    strcpy(x, a);
    strcpy(a, b);
    strcpy(b, x);
}

int main()
{
    char a[N+1], b[N+1], c[N+1];
    scanf("%s%s", a, b);
    memset(c, ' ', N+2);

    //调整被除数与除数的顺序
    if (strlen(a) < strlen(b))
        swap(a, b);
    else if (strlen(a) == strlen(b)) {
        if (strcmp(a, b)==0) {
            puts("a-b=0");
            return 0;
        } else if (strcmp(a, b) < 0)
            swap(a, b);
    }

    minus_number(a, b, c);
    printf("a-b=%s\n", c);

    return 0;
}