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
    account pe[1000];
    int get_one, pay_one;
    int i, j;

    for (i-0; 1; i++) {
        puts("输入个人财务信息（0为结束）：");
        printf("请输入姓名：");
        scanf("%s", pe[i].name);
        if (pe[i].name == '0')
            break;
        printf("请输入年份：");
        scanf("%d", &pe[i].year);

        pe[i].get = 0;
        pe[i].pay = 0;
        pe[i].total = 0;

        puts("请输入收入(输入0结束)：");
        while (1) {
            scanf("%d", &get_one);
            if (!get_one)
                break;
            pe[i].get += get_one;
        }
        puts("请输入支出(输入0结束)：");
        while (1) {
            scanf("%d", &pay_one);
            if (!pay_one)
                break;
            pe[i].pay += pay_one;
        }
        pe[i].total = pe[i].get - pe[i].pay;
        if (pe[i].total < 0)
            pe[i].total = 0;

        printf("%s的%d年财务情况：\n", pe[i].name, pe[i].year);
        printf("收入总额为%d元，支出总额为%d元，存款总额为%d元\n", pe[i].get, pe[i].pay, pe[i].total);
    }
    return 0;
}
