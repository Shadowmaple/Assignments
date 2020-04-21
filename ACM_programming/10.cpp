# include <iostream>
# include <string>
# include <map>
using namespace std;

int main() {
    int a, k;
    cin >> a >> k;
    string dic[k];
    string s;
    for (int i = 0; i < k; i++)
        cin >> dic[i];
    cin >> s;

    // 建图
    // 入度
    int in[26] = {0};
    int point[26][26] = {0}, use[26] = {0};
    for (int i = 1; i < k; i++) {
        for (int j = 0; j < dic[i].length() && j < dic[i-1].length(); j++) {
            if (dic[i][j] == dic[i-1][j]) continue;
            int x = dic[i-1][j] - 'a';
            int y = dic[i][j] - 'a';
            point[x][y] = 1;
            in[y]++;
            use[x] = use[y] = 1;
            break;
        }
    }

    // 统计字母个数
    int count = 0;
    for (int i = 0 ; i < 26; i++) {
        if (use[i]) {
            count++;
        }
    }
    if (count != a) {
        cout << "0" << endl;
        return 0;
    }

    map<char, char> mp;
    for (int i = 0; i < a; i++) {
        int idx = -1;
        // 获取入度为0的点
        for (int j = 0; j < 26; j++) {
            if (use[j] && in[j] == 0) {
                idx = j;
                break;
            }
        }
        if (idx == -1) {
            cout << "0" << endl;
            return 0;
        }

        // 去除该点所连的边
        for (int j = 0; j < 26; j++) {
            if (!use[j] || !point[idx][j]) continue;
            in[j]--;
            point[idx][j] = 0;
        }

        in[idx] = -1;
        mp[idx + 'a'] = i + 'a';
    }

    for (char c : s) {
        cout << mp[c];
    }
    cout << endl;

    return 0;
}