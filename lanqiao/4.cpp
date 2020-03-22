# include <iostream>
# include <cstring>
using namespace std;

int main() {
    char c[120];
    scanf("%s", c);
    bool flag = false;
    int level = 1, num = 0;
    for (int i = 0; i < strlen(c); i++) {
        if (c[i]=='a' || c[i]=='e' || c[i]=='i' || c[i]=='o' || c[i]=='u')
            flag = true;
        else flag = false;
        // 辅音字母阶段
        if (level % 2 == 1) {
            // 辅音字母
            if (!flag) {
                num++;
                continue;
            }
            // 元音字母
            // 之前没有辅音出现，不满足阶段变换的条件
            if (!num) {
                cout << "no" << endl;
                return 0;
            }
            level++;
            num = 1;

        // 元音字母阶段
        } else {
            // 元音字母
            if (flag) {
                num++;
                continue;
            }
            // 辅音字母
            // 之前没有元音出现，不满足阶段变换的条件
            if (!num) {
                cout << "no" << endl;
                return 0;
            }
            level++;
            num = 1;
        }
        if (level > 4) break;
    }
    if (level != 4) cout << "no" << endl;
    else cout << "yes" << endl;
    return 0;
}