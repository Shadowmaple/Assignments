# include <stdio.h>
# include <string.h>

void reserve(int *link, int k, int x)
{
    int a[k];
    int i, j;
    for (i=k-1, j=0; i >= 0; i--, j++) {
        a[j] = link[i];
    }
    for (i=0; i < k; i++)
        link[i] = a[i];
}

int main()
{
    int i, j;
    int K;
    printf("���뷴ת����");
    scanf("%d", &K);
    int n;
    printf("��������ڵ�����");
    scanf("%d", &n);
    int link[n];
   // int link[6] = {1, 2, 3, 4, 5, 6};
    puts("��������ڵ㣺");
    for (i=0; i < n; i++) {
        printf(" ");
        scanf("%d", link+i);
        if (i != n-1)
     //       printf("->");
            puts("��");
    }
    for (i=0; i < n / K; i++) {
            reserve(link + i * K, K, i * K);
    }
    puts("��ת�������");
    for (i=0; i < n; i++)
        printf("%d%s", link[i], (i==n-1)? "\n":"->");

    return 0;
}
