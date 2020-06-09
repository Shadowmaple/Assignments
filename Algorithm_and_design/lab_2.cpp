// 最近对问题，设pn=(xn, yn)，平面上有p1,p2,...,pn等n个点构成的集合S，
// 设计算法找出集合S中距离最近的点对

# include <iostream>
# include <math.h>
# include <algorithm>
using namespace std;

# define INF 999999

int n;
bool ending;

class Point {
public:
    int x, y;
    Point() {};
    Point(int x, int y) {
        this->x = x;
        this->y = y;
    };
    double distance(Point p) {
        return sqrt(pow(x - p.x, 2) + pow(y - p.y, 2));
    };
    static bool xcmp(Point a, Point b) {
        return a.x < b.x;
    }
    static bool ycmp(Point a, Point b) {
        return a.y < b.y;
    }
};

Point s[100000];

// 分治法
double divide(int l, int r) {
    double d1, d2, d;
    if (r - l == 1) return s[l].distance(s[r]);
    else if (r - l == 2) {
        d1 = s[l].distance(s[l+1]);
        d2 = s[l].distance(s[r]);
        d = s[l+1].distance(s[r]);
        // printf("%f %f %f\n", d1, d2, d);
        d = d1 < d ? d1 : d;
        d = d < d2 ? d : d2;
        return d;
    }

    int mid = (l + r) / 2;
    d1 = divide(l, mid);
    d2 = divide(mid+1, r);
    d = d1 > d2 ? d2 : d1;
    // printf("-- %.2f %.2f\n", d1, d2);

    Point p[n];
    int k = 0;
    for (int i = mid; i > l && s[mid].x - s[i].x < d; i--)
        p[k++] = s[i];
    for (int i = mid+1; i < r && s[i].x - s[mid].x < d; i++)
        p[k++] = s[i];

    sort(p, p+k, p[0].ycmp);
    for (int i = 0; i < k-1; i++) {
        for (int j = i+1; j < k; j++) {
            if (p[i].y - p[j].y >= d) break;
            d1 = p[i].distance(p[j]);
            d = d1 < d ? d1 : d;
        }
    }
    return d;
}

// 分治算法
void DivideMethod() {
    sort(s, s+n, s[0].xcmp);
    divide(0, n-1);
}

// 蛮力法
void Force() {
    double min = INF, d;
    int tar_1, tar_2;
    for (int i = 0; i < n-1; i++) {
        for (int j = i + 1; j < n; j++) {
            d = s[i].distance(s[j]);
            if (min > d) {
                min = d;
                tar_1 = i;
                tar_2 = j;
            }
        }
    }
    // printf("%d %d, distance = %.2f\n", tar_1, tar_2, min);
}

// 计时
void runTime(void (*f)()) {
    cout << "n = " << n << endl;

    clock_t start, end;
    start = clock();

    f();

    end = clock();
    double runTime = (double)(end - start) / CLOCKS_PER_SEC;
    if (runTime >= 60) ending = true;

    cout << "Run time: " << runTime << "s" << endl;
}

// 产生随机数
int proRand(int a, int b) {
    return rand() % (b-a) + a;
}

void sampleData() {
    for (int i = 0; i < n; i++) {
        s[i].x = proRand(-100, 100);
        s[i].y = proRand(-100, 100);
    }
}

int main() {
    n = 5;
    int choices[] = {100, 200, 500, 1000, 2000, 5000, 10000, 50000};
    for (int i = 0; i < 8; i++) {
        n = choices[i];
        ending = false;
        sampleData();
        // runTime(Force);
        runTime(DivideMethod);
    }
    return 0;
}
