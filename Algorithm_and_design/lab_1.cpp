# include <iostream>
# include <cstdlib>
# include <vector>
# include <ctime>
using namespace std;

// 产生随机数
int proRand(int a, int b) {
    return rand() % (b-a) + a;
}

// 样本数据，k组，每组n个
void sampleData(vector<vector<int>>& v, int k, int n) {
    for (int i = 0; i < k; i++) {
        vector<int> num;
        for (int j = 0; j < n; j++) {
            int n = proRand(0, 100);
            num.push_back(n);
        }
        v.push_back(num);
    }
}

// 冒泡排序
void bubbleSort(vector<int>& num) {
    int n = num.size();
    for (int i = 0; i < n-1; i++) {
        for (int j = i+1; j < n; j++) {
            if (num[i] > num[j]) swap(num[i], num[j]);
        }
    }
}

// 快速排序
void quickSort(vector<int>& num, int left, int right) {
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
    quickSort(num, left, a - 1);
    quickSort(num, a + 1, right);
}

void QuickSort(vector<int>& num) {
    quickSort(num, 0, num.size()-1);
}

// 归并排序
void mergeSort(vector<int>& num, int left, int right) {
    if (left >= right) return ;
    int mid = (left + right) / 2;
    mergeSort(num, left, mid);
    mergeSort(num, mid+1, right);

    int i = left, j = mid+1;
    // vector<int> result;
    int result[right-left+1], k = 0;
    while (i <= mid && j <= right) {
        if (num[i] <= num[j])
            // result.push_back(num[i++]);
            result[k++] = num[i++];
        else
            result[k++] = num[j++];
    }
    while (i <= mid) result[k++] = num[i++];
    while (j <= right) result[k++] = num[j++];
    for (int i = left, k = 0; i <= right; i++, k++)
        num[i] = result[k];
}

void MergeSort(vector<int>& num) {
    mergeSort(num, 0, num.size()-1);
}

// 计时
void runTime(vector<vector<int>> nums, void (*sort)(vector<int>& num)) {
    int size = nums.size();
    clock_t start, end, startPart;
    start = clock();

    for (int i = 0; i < size; i++)
        sort(nums[i]);

    end = clock();
    double runTime = (double)(end - start) / CLOCKS_PER_SEC;
    cout << "Total: " << runTime << endl;
    cout << "Average: " << runTime / size << endl;
}

int main() {
    srand(3);
    vector<int> n = {100, 200, 500, 1000, 2000, 5000, 10000, 20000, 30000, 40000, 50000};

    // cout << "Bubble Sort" << endl;
    // cout << "Quick Sort" << endl;
    cout << "Merge Sort" << endl;

    for (int i = 0; i < n.size(); i++) {
        vector<vector<int>> nums;
        sampleData(nums, 1000, n[i]);
        printf("T(%d)：\n", n[i]);
        // runTime(nums, QuickSort);
        // runTime(nums, bubbleSort);
        runTime(nums, MergeSort);
        cout << "----" << endl;
    }

    return 0;
}