# include <iostream>
using namespace std;

int main() {
    long n;
    cin >> n;
    int count = 0;
    for (long i = n; i > 0; i--) {
        int pre = -1, cur;
        bool flag = true;
        long k = i;
        while (k) {
            cur = k % 10;
            k /= 10;
            if (pre != -1 && cur > pre) {
                flag = false;
                break;
            }
            pre = cur;
        }
        if (flag) count++;
    }
    cout << count << endl;
    return 0;
}