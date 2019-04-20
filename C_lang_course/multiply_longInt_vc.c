//长整数乘法
//环境：windows vc6.0

#include <stdio.h>
#include <string.h>

#define N 30

//清除字符串前面的'0'
void clear_zero(char s[])
{
    int i = 0;
    while (s[i] == '0')
        i++;
    strcpy(s, s+i);
}

void add_number(char c[], char n[])
{
    int more = 0, num;
    int i=strlen(n)-1, j=2*N;

    for (; i>=0; i--, j--) {
        num = (n[i] - '0') + (c[j] - '0') + more;
        //进位数
        more = num / 10;
        //相加后该位的结果
        c[j] = num % 10 + '0';
    }
}

void multiply_number(int num, char b[], char n[], int index)
{
    int more = 0, mul, i;
    for (i = strlen(b)-1; i>=0; i--, index--) {
        mul = num * (b[i] - '0') + more;
        //获取十位数，即进位数
        more = mul / 10;
        //个位数，赋值给n[index]
        n[index] = mul % 10 + '0';
    }

    //多出的进位
    n[index] = more + '0';
}

int main()
{
    char a[N+1], b[N+1], c[2*N+1];
    char n[2*N+1];
    int len_ab, zero_num, index;
    int i;
    
    puts("Please enter the number a and b:");
    printf("a = ");
    scanf("%s", a);
    printf("b = ");
    scanf("%s", b);
    //初始化，各字符为0
    memset(c, '0', 2*N+1);

    //从a的各位开始乘
    for (i = strlen(a)-1; i >= 0; i--) {
        zero_num = strlen(a) - i - 1;
        //a和b字符串的长度之和
        len_ab = strlen(a) + strlen(b);

        //存储数与另一位长整数相乘的字符串
        memset(n, '0', len_ab+1);
        
        index = len_ab - zero_num - 1;

        //计算各位数(后有零)与另一位长整数相乘
        multiply_number(a[i] - '0', b, n, index);
        n[len_ab] = '\0';

        //各位数与另一位长整数的乘积累加
        add_number(c, n);
    }

	c[2*N+1] = '\0';
    clear_zero(c);
    printf("a * b = %s\n", c);

    return 0;
}
