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
        puts("������˲�����Ϣ��0Ϊ��������");
        printf("������������");
        scanf("%s", pe[i].name);
        if (pe[i].name == '0')
            break;
        printf("��������ݣ�");
        scanf("%d", &pe[i].year);

        pe[i].get = 0;
        pe[i].pay = 0;
        pe[i].total = 0;

        puts("����������(����0����)��");
        while (1) {
            scanf("%d", &get_one);
            if (!get_one)
                break;
            pe[i].get += get_one;
        }
        puts("������֧��(����0����)��");
        while (1) {
            scanf("%d", &pay_one);
            if (!pay_one)
                break;
            pe[i].pay += pay_one;
        }
        pe[i].total = pe[i].get - pe[i].pay;
        if (pe[i].total < 0)
            pe[i].total = 0;

        printf("%s��%d����������\n", pe[i].name, pe[i].year);
        printf("�����ܶ�Ϊ%dԪ��֧���ܶ�Ϊ%dԪ������ܶ�Ϊ%dԪ\n", pe[i].get, pe[i].pay, pe[i].total);
    }
    return 0;
}
