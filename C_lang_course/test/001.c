// 书本p374 (2) 题，并将结果输出到文件中

# include <stdio.h>

struct product
{
	char dm[5], mc[11];
	int dj, sl;
	long je;
} pro[100];

int mian()
{
	int i, j;
	int con;
	FILE *f;

	while (1) {
		printf("输入1继续，0退出：");
		scanf("%d", &con);
		if (!con)
			break;

		for (i=0; 1; i++) {
			scanf("%s%s%d%d", pro[i].dm, pro[i].mc, &pro[i].dj, &pro[i].sl);
			pro[i].je = pro[i].dj * pro[i].sl;
		}
	}

	return 0;
}
