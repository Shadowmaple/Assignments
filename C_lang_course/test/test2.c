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

    printf("������������");
    scanf("%s", pe.name);
    printf("��������ݣ�");
    scanf("%d", &pe.year);

    puts("����������(����0����)��");
    while (1) {
        scanf("%d", &get_one);
        if (!get_one)
            break;
        pe.get += get_one;
    }
    puts("������֧��(����0����)��");
    while (1) {
        scanf("%d", &pay_one);
        if (!pay_one)
            break;
        pe.pay += pay_one;
    }
    pe.total = pe.get - pe.pay;
    if (pe.total < 0)
        pe.total = 0;

    printf("%s��%d����������\n", pe.name, pe.year);
    printf("�����ܶ�Ϊ%dԪ��֧���ܶ�Ϊ%dԪ������ܶ�Ϊ%dԪ\n", pe.get, pe.pay, pe.total);
    return 0;
}
