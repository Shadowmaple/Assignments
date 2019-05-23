#include <stdio.h>

struct account_p
{
    char name[10];
    int year;
    int pay;
    int get;
    int total;
};

typedef struct account_p account;

int main()
{
    account pe;
    int get_one, pay_one;

    pe.get = 0;
    pe.pay = 0;
    pe.total = 0;

    printf("请输入姓名：");
    scanf("%s", pe.name);
    printf("请输入年份：");
    scanf("%d", &pe.year);

    puts("请输入收入(输入0结束)：");
    while (1) {
        scanf("%d", &get_one);
        if (!get_one)
            break;
        pe.get += get_one;
    }
    puts("请输入支出(输入0结束)：");
    while (1) {
        scanf("%d", &pay_one);
        if (!pay_one)
            break;
        pe.pay += pay_one;
    }
    pe.total = pe.get - pe.pay;
    if (pe.total < 0)
        pe.total = 0;

    printf("%s的%d年财务情况：\n", pe.name, pe.year);
    printf("收入总额为%d元，支出总额为%d元，存款总额为%d元\n", pe.get, pe.pay, pe.total);
    return 0;
}
