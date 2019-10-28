# include <stdio.h>
# include <stdlib.h>

int strLength(char *S) {
    int cout = 0;
    while (S[cout++] != '\0') ;
    return cout - 1;
}

// 连接串S和T，用V接收
void strCon(char *S, char *T, char *V) {
    int index = 0, i = 0;
    while (S[i] != '\0')
        V[index++] = S[i++];
    i = 0;
    while (T[i] != '\0')
        V[index++] = T[i++];
    V[index] = '\0';
}

// 用sub返回S中第pos个起长为len的子串
void subString(char *sub, char *S, int pos, int len) {
    int slen = strLength(S);
    if (pos < 0 || pos > slen || len < 0 || slen < len + pos) {
        puts("Get subString error");
        return ;
    }

    int index = 0;
    for (int i = pos; i < pos + len; i++)
        sub[index++] = S[i];
    sub[index] = '\0';
}

int main() {
    char a[] = "2asdfwegr22", b[20] = "aaabv";
    char c[20], d[20];
    strCon(a, b, c);
    subString(d, a, 2, 4);
    printf("%s, %s, %s, %s\n", a, b, c, d);
    return 0;
}