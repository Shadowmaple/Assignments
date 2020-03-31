// 大整数加法

# include <iostream>
# include <cstring>
using namespace std;

int main() {
    char n1[201], n2[201];
    cin >> n1 >> n2;

    int len = strlen(n1) + strlen(n2);
    char num[len+1];

    int flag = 0;
    int i = strlen(n1)-1, j = strlen(n2)-1, k = len-1;
    for (; i >= 0 && j >= 0; i--, j--) {
        int n = (n1[i]-'0') + (n2[j]-'0') + flag;
        flag = n / 10;
        num[k--] = n % 10 + '0';
    }
    while (i >= 0) {
        int n = n1[i--] - '0' + flag;
        flag = n / 10;
        num[k--] = n % 10 + '0';
    }
    while (j >= 0) {
        int n = n2[j--] - '0' + flag;
        flag = n / 10;
        num[k--] = n % 10 + '0';
    }
    if (flag) num[k--] = '1';

    num[len] = '\0';
    strcpy(num, num+k+1);

    cout << num << endl;
    return 0;
}