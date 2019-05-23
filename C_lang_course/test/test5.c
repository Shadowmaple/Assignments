# include <stdio.h>
# include <string.h>

int totsubstrnum(char *str, char *substr)
{
    int i, j;
    int num = 0;
    int flag = 0;
    for (i=0; i < strlen(str); i++) {
        if (str[i] != substr[0])
            continue;
        flag = 1;
        for (j=0; j < strlen(substr); i++, j++) {
            if (str[i] != substr[j]) {
                flag = 0;
                break;
            }
        }
        if (flag) {
            num++;
        }
    }
    return num;
}

int main()
{
    int i, j;
    int num;

    char str[100], substr[100];
    scanf("%s%s", str, substr);

    num = totsubstrnum(str, substr);
    printf("%d\n", num);

    return 0;
}
