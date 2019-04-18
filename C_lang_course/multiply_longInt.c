//长整数乘法

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
    int more = 0;
    //i对应n[]，j对应c[]
    for (int i=strlen(n)-1, j=2*N; i>=0; i--, j--) {
        int num = (n[i] - '0') + (c[j] - '0') + more;
        //进位
        more = num / 10;
        //相加后该位的结果
        c[j] = num % 10 + '0';
    }
}

void multiply_number(int num, char b[], char n[], int index)
{
    int more = 0;
    for (int i = strlen(b)-1; i>=0; i--, index--) {
        int mul = num * (b[i] - '0') + more;
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
    
    printf("a = ");
    scanf("%s", a);
    printf("b = ");
    scanf("%s", b);
    //初始化，各字符为0
    memset(c, '0', 2*N+1);

    //从a的各位开始乘
    for (int i = strlen(a)-1; i >= 0; i--) {
        int num = a[i] - '0';
        int zero_num = strlen(a) - i - 1;
        //a和b字符串的长度之和
        int len_ab = strlen(a) + strlen(b);

        //存储数与另一位长整数相乘的字符串
        char n[len_ab];
        memset(n, '0', len_ab+1);
        
        int index = len_ab - zero_num - 1;

        //计算各位数(后有零)与另一位长整数相乘
        multiply_number(num, b, n, index);
        n[len_ab] = '\0';
//        printf("n=%s\n", n);

        //各位数与另一位长整数的乘积累加
        add_number(c, n);
    }

    clear_zero(c);
    printf("a * b = %s\n", c);

    return 0;
}