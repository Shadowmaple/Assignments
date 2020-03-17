// 小球下落

# include <iostream>
using namespace std;

int main() {
    int D, I;
    while (scanf("%d%d", &D, &I) != EOF) {
        int node[(1 << D) - 1] = {0};
        while (I--) {
            int po = 1, curPo = 1;
            for (int dp = 2; dp <= D; dp++) {
                if (node[po-1]) curPo = po * 2 + 1;
                else curPo = po * 2;
                node[po-1] = 1 - node[po-1];
                po = curPo;
            }
            if (!I) cout << po << endl;
        }
    }
    return 0;
}