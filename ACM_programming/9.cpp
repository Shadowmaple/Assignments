# include <iostream>
# include <vector>
# include <algorithm>
# include <fstream>
using namespace std;

typedef struct {
    int xmin, xmax, ymin, ymax;
} PPTNode;

typedef struct {
    int num, ch;
} Va;

// void pu(vector<int>& a){
//     puts("pu begin");
//     for (int i = 0; i < a.size(); i++) {
//         cout << a[i] << ' ';
//     }
//     cout << endl;
// }

// void cu(vector<vector<int>> p) {
//     puts("cu begin");
//     for (int i = 0; i < p.size(); i++) {
//         for (int j = 0; j < p[i].size(); j++) {
//             cout << p[i][j] << ' ';
//         }
//         cout << endl;
//     }
// }

bool cmp(Va a, Va b) {
    return a.ch <= b.ch;
}

int main() {
    ifstream ifile("Slides.txt");
    int n;
    // cin >> n;
    ifile >> n;
    PPTNode nodes[n];
    vector<vector<int>> points(n);
    vector<int> declude;
    for (int i = 0; i < n; i++) {
        // cin >> nodes[i].xmin >> nodes[i].xmax >> nodes[i].ymin >> nodes[i].ymax;
        ifile >> nodes[i].xmin >> nodes[i].xmax >> nodes[i].ymin >> nodes[i].ymax;
        // printf("%d %d %d %d\n", nodes[i].xmin, nodes[i].xmax, nodes[i].ymin, nodes[i].ymax);
    }

    for (int i = 0; i < n; i++) {
        int x, y;
        // cin >> x >> y;
        ifile >> x >> y;
        for (int j = 0; j < n; j++) {
            if (nodes[j].xmin <= x && nodes[j].xmax >= x && nodes[j].ymin <= y && nodes[j].ymax >= y) {
                // points[i].nums.push_back(j);
                points[i].push_back(j);
            }
        }
        if (points[i].size() == 1) {
            declude.push_back(points[i][0]);
        } else if (points[i].size() == 0) {
            cout << "None" << endl;
            return 0;
        }
    }

    ifile.close();

    for (int i = 0; i < declude.size(); i++) {
        for (int j = 0; j < n; j++) {
            if (points[j].size() == 1) continue;

            for (auto it = points[j].begin(); it < points[j].end(); it++) {
                if (*it == declude[i]) {
                    points[j].erase(it);
                    break;
                }
            }
            if (points[j].size() == 1)
                declude.push_back(points[j][0]);
        }
        // cu(points);
    }

    bool exist[n] = {false};
    for (int i = 0; i < n; i++) {
        if (points[i].size() > 1) {
            cout << "None" << endl;
            return 0;
        }
        int num = points[i][0];
        if (exist[num]) {
            cout << "None" << endl;
            return 0;
        }
        exist[num] = true;
    }

    Va nums[n];
    for (int i = 0; i < n; i++) {
        nums[i].num = i + 1;
        nums[i].ch = points[i][0];
    }

    sort(nums, nums + n, cmp);

    ofstream ofile("Slides_out.txt");

    for (int i = 0; i < n; i++)
        ofile << char(nums[i].ch + 'A') << ' ' << nums[i].num << endl;
        // cout << char(nums[i].ch + 'A') << ' ' << nums[i].num << endl;

    ofile.close();

    return 0;
}