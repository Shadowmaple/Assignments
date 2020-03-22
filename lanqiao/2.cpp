# include <iostream>
# include <algorithm>
using namespace std;

int main() {
    int n;
    cin >> n;
    int a[n];
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    sort(a, a+n);
    int num = 0;
    for (int i = 1; i < n-1; i++) {
        if (a[i] > a[i-1] && a[i] < a[i+1])
            num++;
    }
    cout << num << endl;
    return 0;
}