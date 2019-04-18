//长整数乘法

#include <stdio.h>
#include <string.h>

void clear_zero(char s[])
{
    int i = 0;
    while (s[i] == '0')
        i++;
    strcpy(s, s+i);
}

void add_number(char c[], char n[])
{

}

void multiply_number(int num, char b[], char n[], int index)
{
    int more = 0;
    for (int i = strlen(b), j = index; i>=0; i--, j--) {
        int mul = num * (b[i] - '0') + more;
        //获取十位数，即进位数
        more = mul / 10;
        //获取个位数，即保留数
        int m = more % 10;
        n[j] = m + '0';
    }
}

int main()
{
    char a[N+1], b[N+1], c[2N];
    
    printf("a=");
    scanf("%s", a);
    printf("b=");
    scanf("%s", b);
    memset(c, '0', 2N+1);

    //从各位开始乘
    for (int i = strlen(a)-1; i >= 0; i--) {
        //转换为整数
        int num = a[i] - '0';
        int zero_num = strlen(a) - i - 1;

        //存储数与另一位长整数相乘的字符串
        char n[strlen(b) + 7];
        memset(n, '0', strlen(b)+7);

        int index = strlen(b) + 6 - zero_num - 1;
/*
        for (int j=0, k=strlen(b)+1; j<zero_num; j++, k--) {
            n[k] = '0';
        }
*/
        //计算各位数(后有零)与另一位长整数相乘
        multiply_number(num, b, n, index);

        //各位数与另一位长整数的乘积累加
        add_number(c, n);
    }

    printf("a*b=%s\n", c);

    return 0;
}