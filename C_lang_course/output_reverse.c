//汉字倒序输出

# include <stdio.h>
# include <string.h>

int main()
{
	char str[13] = "华中师大";
	char x[4];
	int i;
	for (i = strlen(str) - 3; i >= 0; i -= 3) {
		strncpy(x, str + i, 3);
		x[3] = '\0';
		printf("%s", x);
	}
	putchar('\n');

	return 0;
}
