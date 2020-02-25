// 完美立方

# include <iostream>
using namespace std;

int main() {
    int n;
    cin >> n;
    // a,b,c,d > 1
    for (int a = 2; a <= n; a++) {
        for (int b = 2; b < a; b++) {
            for (int c = b; c < a; c++) {
                for (int d = c; d < a; d++) {
                    if (a*a*a != b*b*b + c*c*c + d*d*d) continue;
                    printf("Cube=%d,triple=(%d,%d,%d)\n", a, b, c, d);
                }
            }
        }
    }
    return 0;
}