// 0/1背包问题实验

# include <iostream>
# include <ctime>
using namespace std;

int n, C;
int w[2000], v[2000];
int max_value;
bool ending;

void backTracking_so(int i, int weight, int value, int x[], int cur[]) {
    if (i == n) {
        if (max_value < value) {
            max_value = value;
            for (int i = 0; i < n; i++) x[i] = cur[i];
        }
        return ;
    }

    if (C - weight >= w[i]) {
        cur[i] = 1;
        backTracking_so(i+1, weight+w[i], value+v[i], x, cur);
    }

    cur[i] = 0;
    backTracking_so(i+1, weight, value, x, cur);
}

// 回溯法
void backTracking() {
    max_value = 0;
    int x[n], cur[n];
    backTracking_so(0, 0, 0, x, cur);

    // for (int i = 0; i < n; i++)
    //     cout << x[i] << ' ';
    // cout << "\nvalue = " << max_value << endl;
}

// 动态规划
void dp() {
    int value[n+1][C+1];
    for (int i = 0; i <= n; i++) value[i][0] = 0;
    for (int i = 0; i <= C; i++) value[0][i] = 0;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= C; j++) {
            // w[i-1]为第i个物品的质量，v[i-1]亦同
            if (j < w[i-1]) value[i][j] = value[i-1][j];
            else value[i][j] = max(value[i-1][j], value[i-1][j - w[i-1]] + v[i-1]);
        }
    }

    int x[n] = {0};
    int j = C;
    for (int i = n; i > 0; i--) {
        if (value[i][j] > value[i-1][j]) {
            x[i-1] = 1;
            j -= w[i-1];
        }
    }

    // for (int i = 0; i < n; i++)
    //     cout << x[i] << ' ';
    // cout << "\nvalue = " << value[n][C] << endl;
}

void force_so(int i, int weight, int value, int x[], int cur[]) {
    if (i == n) {
        if (weight <= C && max_value < value){
            max_value = value;
            for (int i = 0; i < n; i++) x[i] = cur[i];
        }
        return ;
    }

    cur[i] = 1;
    force_so(i+1, weight+w[i], value+v[i], x, cur);
    cur[i] = 0;
    force_so(i+1, weight, value, x, cur);
}

// 蛮力法
void force() {
    max_value = 0;
    int x[n], cur[n];
    force_so(0, 0, 0, x, cur);

    // for (int i = 0; i < n; i++)
    //     cout << x[i] << ' ';
    // cout << "\nvalue = " << max_value << endl;
    // cout << "Run time: " << runTime << endl;
}

// // 计时
void runTime(void (*f)()) {
    clock_t start, end;
    start = clock();

    f();

    end = clock();
    double runTime = (double)(end - start) / CLOCKS_PER_SEC;

    cout << "n = " << n << endl;
    cout << "Run time: " << runTime << "s" << endl;

    if (runTime >= 60) ending = true;
}

// 产生随机数
int proRand(int a, int b) {
    return rand() % (b-a) + a;
}

void sampleData() {
    C = proRand(10, n * 2);
    for (int i = 0; i < n; i++) {
        w[i] = proRand(1, 20);
        v[i] = proRand(10, 50);
    }
}

int main() {
    int choices[] = {10, 15, 20, 25, 30, 35, 40, 45, 50, 55, 60};
    int choices_2[] = {100, 200, 300, 400, 500, 600, 700, 800, 900, 1000, 2000};

    srand(3);

    puts("\n------ dynamic programming -------\n");
    // puts("\n------ backtracking -------\n");
    // puts("\n------ force method -------\n");

    ending = false;
    for (int i = 0; i < 11; i++) {
		if (ending) break;

		// n = choices[i];
        n = choices_2[i];
		sampleData();

		runTime(dp);
		// runTime(backTracking);
		// runTime(force);

		puts("-------------");
	}

    // force();
    // backTracking();
    // dp();

    return 0;
}

// n = 5, C = 6
// w = 3,2,1,4,5
// v = 25,20,15,40,50
// 0 0 1 0 1 value = 65

// n = 5, C =10
// w = 2,2,6,5,4
// v = 6,3,5,4,6
// 1,1,0,0,1 value = 15
