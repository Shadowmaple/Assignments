// 在1至2019中，有多少个数的数位中包含数字9？

# include <iostream>
using namespace std;

int main() {
    int count = 0;
    for (int i = 1; i <= 2019; i++) {
        int k = i;
        while (k) {
            if (k % 10 == 9) {
                count++;
                break;
            }
            k /= 10;
        }
    }
    cout << count << endl;
    return 0;
}