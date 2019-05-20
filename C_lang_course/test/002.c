// 书上p254 (4)题，将结果引入文件中，并通过文件打印出来

# include <stdio.h>
# include <string.h>

void JsSort(char *str)
{
	int i, j;
	char str_re[100];
	char swap;

	for (i=0; i < strlen(str); i++) {
		if (i % 2 == 0) {
			str_re[i] = str[i];
			continue;
		}
		str_re[i] = str[i];
		for (j=1; j < i; j += 2) {
			if (str_re[j] < str_re[i]) {
				swap = str_re[i];
				str_re[i] = str_re[j];
				str_re[j] = swap;	
			}
		}
	}
	str_re[i] = '\0';
	strcpy(str, str_re);
}

int main()
{
	char str[100];
	int i, j;
	FILE *f;

	scanf("%s", str);
	JsSort(str);
	printf("%s\n", str);

	f = fopen("002_file.txt", "w+");
	fputs(str, f);
	fgets(str, strlen(str), f);
	printf("%s\n", str);

	fclose(f);

	return 0;
}
