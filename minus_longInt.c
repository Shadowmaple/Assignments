#include <stdio.h>
#include <string.h>

#define N 20

int flag = 0;

void clear_blankAndZero(char s[])
{
    int i = 0;
    while (s[i] == ' ')
        i++;
    strcpy(s, s+i);
    //去掉开头的零
    if (s[0]-'0' == 0)
        strcpy(s, s+1);
}

void minus_number(char a[], char b[], char c[])
{
    int i=strlen(a)-1, j=strlen(b)-1, k=N;

    for (; i>=0 && j>=0; i--, j--, k--) {
        int a_n = a[i] - '0' - flag;
        flag = 0;

        int n = (a_n) - (b[j]-'0');
        if (n >= 0) {
            c[k] = n + '0';
        } else {
            //不足则借一
            flag = 1;
            c[k] = 10 + n + '0';
        }
    }
    //被除数长度大于除数时多的部分
    while (i >= 0) {
        c[k--] = a[i--] - '0' - flag + '0';
    }
//    c[N+1] = '\0';
    clear_blankAndZero(c);
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