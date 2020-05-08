// 最长子序列

# include <iostream>
# include <string>
using namespace std;

int CommonOrder(string s1, string s2) {
    int len1 = s1.length(), len2 = s2.length();
    int L[len1+1][len2+1];
    // 初始化
    for (int i = 0; i <= len1; i++)
        L[i][0] = 0;

    // 初始化
    for (int j = 0; j <= len2; j++)
        L[0][j] = 0;

    for (int i = 1; i <= len1; i++) {
        for (int j = 1; j <= len2; j++) {
            if (s1[i-1] == s2[j-1])
                L[i][j] = L[i-1][j-1] + 1;
            else
                L[i][j] = max(L[i-1][j], L[i][j-1]);
        }
    }

    // for (int i = 0; i <= len1; i++) {
    //     for (int j = 0; j <= len2; j++)
    //         cout << L[i][j] <<" ";
    //     putchar('\n');
    // }

    return L[len1][len2];
}

int main() {
    string s1, s2;
    cin >> s1 >> s2;
    int n = CommonOrder(s1, s2);
    cout << n << endl;

    return 0;
}