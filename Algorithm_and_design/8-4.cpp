// n皇后问题，并输出 n 皇后问题的所有解

# include <iostream>
# include <stack>
using namespace std;

int x[100];
int count = 0;
stack<int> sk;

// 判断是否冲突
bool Place(int k) {
    for (int i = 0; i < k; i++) {
        if (x[i] == x[k] || abs(i-k) == abs(x[i]-x[k]))
            return true;
    }
    return false;
}

// 求解n皇后
// x[i]表示第i行的皇后摆放在第x[i]列的位置
void Queen(int n) {
    int k = 0;
    while (k >= 0) {
        // 避免冲突，摆放在某一列
        while (x[k] < n && Place(k))
            x[k]++;

        // 成功摆放，保存一个皇后
        if (x[k] < n)
            sk.push(x[k]);
        else {
            // 回溯，重新摆放上一个皇后
            x[k--] = 0;
            x[k]++;
            sk.pop();
            continue;
        }

        // 皇后已全部摆放，输出结果
        if (k == n-1) {
            count++;
            for (int i = 0; i < sk.size(); i++) {
                printf("%d-%d\t", i+1, x[i]+1);
                // cout << x[i] + 1 << " ";
            }
            cout << endl;
        }
        // 下一个皇后
        k++;
    }
    printf("共%d种方式\n", count);
}

int main() {
    int n = 8;

    // 初始化列
    for (int i = 0; i < n; i++)
        x[i] = 0;

    Queen(n);

    return 0;
}
