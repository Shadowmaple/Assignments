// 书本p374 (2) 题，并将结果输出到文件中

# include <stdio.h>
# include <string.h>

struct product
{
	char dm[5], mc[11];
	int dj, sl;
	long je;
} pro[100];

void SortDat(struct product *p, int total)
{
	int i, j;
	struct product swap;
	int cmp;

	for (i=0; i < total-1; i++) {
		for (j=0; j < i; j++) {
			cmp = strcmp(p[i].dm, p[j].dm);
			if (cmp > 0 || !cmp && p[i].je > p[j].je) {
				swap = p[i];
				p[i] = p[j];
				p[j] = swap;
			}
		}
	}
}

int main()
{
	int i, j;
	int con;
	int total = 0;
	FILE *f;

		for (i=0; 1; i++) {
			if (i) {
				printf("输入1继续，0退出：");
				scanf("%d", &con);
				if (!con)
					break;
			}
			scanf("%s%s%d%d", pro[i].dm, pro[i].mc, &pro[i].dj, &pro[i].sl);
			pro[i].je = pro[i].dj * pro[i].sl;
		}

	total = i;
	SortDat(pro, total);

	f = fopen("001_file.txt", "w+");
	for (i=0; i < total; i++) {
		printf("%4s %10s %5d %5d %11ld\n", pro[i].dm, pro[i].mc, pro[i].dj, pro[i].sl, pro[i].je);
		fprintf(f, "%4s %10s %5d %5d %11ld\n", pro[i].dm, pro[i].mc, pro[i].dj, pro[i].sl, pro[i].je);
	}

	fclose(f);
	return 0;
}
