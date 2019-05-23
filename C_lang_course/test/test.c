#include <stdio.h>
#include <string.h>

char *substr(char *s, int startloc, int len)
{
    char a[1000];
    int i, j;
    for (i=startloc, j=0; i<len+startloc; i++, j++) {
        a[j] = s[i];
    }
    a[j] = '\0';
    return a;
}

int main()
{
    char st[1000], a[1000];
    int start, len, i;

    puts("输入字符串，开始位置和截取长度：");
    scanf("%s%d%d", st, &start, &len);
    printf("%s\n", substr(st, start, len));
    return 0;
}
