# include <iostream>
# include <cstdlib>
# include <vector>
# include <ctime>
using namespace std;

int proRand(int a, int b) {
    return rand() % (b-a) + a;
}

void pubSort(vector<int>& num) {
    for (int i = 0; i < num.size()-1; i++) {
        for (int j = i+1; j < num.size(); j++) {
            if (num[i] > num[j]) swap(num[i], num[j]);
        }
    }
}

void quickSortPa(vector<int>& num, int left, int right) {
    if (left > right) return ;
    int a = left, b = right;
    int key = num[left];
    while (a < b) {
        while (num[b] > key && a < b) b--;
        if (a < b) num[a] = num[b];
        while (num[a] <= key && a < b) a++;
        if (a < b) num[b] = num[a];
    }
    num[a] = key;
    quickSortPa(num, left, a - 1);
    quickSortPa(num, a + 1, right);
}

void quickSort(vector<int>& num) {
    quickSortPa(num, 0, num.size()-1);
}

void runTime(vector<vector<int>> nums, void (*sort)(vector<int>& num)) {
    clock_t start, end, startPart;
    start = clock();
    for (int i = 0; i < 1000; i++) {
        startPart = clock();
        sort(nums[i]);
        double curRunTime = (double)(clock() - startPart) / CLOCKS_PER_SEC;
        // cout << "Test" << i+1 << " n=" << nums[i].size() << ": " << curRunTime << endl;
        cout << "Test" << i+1 << ": " << curRunTime << endl;
    }
    end = clock();
    double runTime = (double)(end - start) / CLOCKS_PER_SEC;
    cout << "Total: " << runTime << endl;
    cout << "Average: " << runTime / 1000 << endl;
}

int main() {
    srand(3);
    vector<vector<int>> nums;
    for (int i = 0; i < 1000; i++) {
        vector<int> num;
        for (int j = 0; j < 1000; j++) {
            int n = proRand(0, 100);
            num.push_back(n);
        }
        nums.push_back(num);
    }

    cout << "Pub Sort" << endl;
    runTime(nums, pubSort);
    // cout << "Quick Sort" << endl;
    // runTime(nums, quickSort);

    return 0;
}