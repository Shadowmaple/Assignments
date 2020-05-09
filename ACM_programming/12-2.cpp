# include <iostream>
# include <vector>
using namespace std;

int main() {
    int k;
    while (scanf("%d", &k) != EOF) {
        int count = 0;
        int kx = k * k;
        vector<int> vx, vy;
        for (int x = 2*k; x < kx*k; x++) {
            for (int y = 2*k; y > k; y--) {
                if (kx != (x - k)*(y - k)) continue;
                vx.push_back(x);
                vy.push_back(y);
                count++;
            }
        }
        cout << count << endl;
        for (int i = 0; i < vx.size(); i++)
            printf("1/%d=1/%d+1/%d\n",k, vx[i], vy[i]);

    }

    return 0;
}