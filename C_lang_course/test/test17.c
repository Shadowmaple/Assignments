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
    printf("输入反转数：");
    scanf("%d", &K);
    int n;
    printf("输入链表节点数：");
    scanf("%d", &n);
    int link[n];
   // int link[6] = {1, 2, 3, 4, 5, 6};
    puts("输入链表节点：");
    for (i=0; i < n; i++) {
        printf(" ");
        scanf("%d", link+i);
        if (i != n-1)
     //       printf("->");
            puts("↓");
    }
    for (i=0; i < n / K; i++) {
            reserve(link + i * K, K, i * K);
    }
    puts("反转后的链表：");
    for (i=0; i < n; i++)
        printf("%d%s", link[i], (i==n-1)? "\n":"->");

    return 0;
}
