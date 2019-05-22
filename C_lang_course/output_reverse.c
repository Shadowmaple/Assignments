//汉字倒序输出

# include <stdio.h>
# include <string.h>

int main()
{
	char str[19] = "华中师范大学";
	char x[4];
	int i, j=1;
	for (i = strlen(str) - 3; i >= 0; i -= 3) {
		strncpy(x, str + i, 3);
		printf("%s", x);
	}
	putchar('\n');

	return 0;
}
