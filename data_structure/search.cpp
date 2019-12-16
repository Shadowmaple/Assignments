// 给定一个整型的无序序列，利用堆排序对其生序排序，然后用二分查找查找给定的关键字
// 若查找成功则返回在有序序列中的位置，否则返回0
// 分别用递归和非递归实现二分查找

# include <iostream>
using namespace std;

// 构建大根堆
void heapBuild(int *num, int size) {
    for (int i = 1; i < size; i++) {
        int index = i;
        int parentIndex = (index - 1) / 2;
        while (num[index] > num[parentIndex]) {
            swap(num[index], num[parentIndex]);
            index = parentIndex;
            parentIndex = (index - 1) / 2;
        }
    }
}

void heapUpdate(int *num, int size) {
    int index = 0, leftIndex = 1, rightIndex = 2;
    int maxIndex;

    while (leftIndex < size) {
        if (rightIndex < size && num[rightIndex] > num[leftIndex])
            maxIndex = rightIndex;
        else
            maxIndex = leftIndex;
        // maxIndex = num[leftIndex] > num[rightIndex] ? leftIndex : rightIndex;

        if (num[maxIndex] < num[index]) break;

        swap(num[index], num[maxIndex]);
        index = maxIndex;
        leftIndex = index * 2 + 1;
        rightIndex = index * 2 + 2;
    }

    // for (int i = 0; i < 8; i++)
    //     cout << num[i] << " ";
    // cout << "--" << size << endl;
}


void heapSort(int *num, int size) {
    // 初始建堆
    heapBuild(num, size);

    while (size > 1) {
        swap(num[size - 1], num[0]);
        heapUpdate(num, --size);
    }
}

// 递归二分查找
int searchRecursion(int *num, int key, int left, int right) {
    if (left > right) return 0;

    int mid = (left + right) / 2;
    if (num[mid] == key) return mid;
    else if (num[mid] > key)
        return searchRecursion(num, key, left, mid - 1);
    else
        return searchRecursion(num, key, mid + 1, right);
}

// 非递归二分查找
int searchNoRecursion(int *num, int key, int size) {
    int left = 0, right = size - 1;

    while (left <= right) {
        int mid = (left + right) / 2;
        if (num[mid] == key) return mid;
        else if (num[mid] > key)
            right = mid - 1;
        else
            left = mid + 1;
    }
    return 0;
}

int main() {
    int num[] = {2, 5, 1, 6, 22, 12, 4, 3};
    heapSort(num, 8);
    for (int i = 0; i < 8; i++)
        cout << num[i] << " ";
    cout << endl;

    int a[] = {1,2,3,4,5};
    cout << searchRecursion(a, 4, 0, 4) << endl;
    cout << searchNoRecursion(a, 4, 5) << endl;

    return 0;
}