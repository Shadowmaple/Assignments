# include <iostream>
# include <math.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    long sum = 1;

    for (int i = 2; i <= n; i++) {
        sum *= i;
        int x = 0;
        int count = 0;
        while (sum > 0 && count < 5) {
            x += (sum % 10) * pow(10, count);
            sum /= 10;
            count++;
        }
        sum = x;
    }

    cout << sum << endl;

    return 0;
}