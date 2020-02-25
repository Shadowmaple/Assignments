// 输出所有形如aabb的四位完全平方数（即前两位数字相等，后两位数字相等）

# include <iostream>
# include <math.h>
using namespace std;

int main() {
    for (int i = 1; i <= 9; i++) {
        int num = i * 1000 + i * 100;
        for (int j = 0; j <= 9; j++) {
            int n = num + j * 10 + j;
            // 判断完全平方数
            int x = sqrt(n);
            if (x*x != n) continue;
            // cout << x << endl;
            cout << n << endl;
        }
    }
    return 0;
}