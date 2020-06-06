// 在有序序列（r1,r2,...rn）中，存在序号i（1<=i<=n），使得 ri=i。
// 请设计一个分治算法找到这个元素，要求在最坏情况下的时间性能为 O(logn)

# include <iostream>
using namespace std;

int n;

void search(int *r, int left, int right) {
    if (left > right) return ;

    int mid = (left + right) / 2;

    if (mid + 1 == r[mid]) {
        cout << "i = " << mid + 1 << endl;
        return ;
    }

    search(r, left, mid-1);
    search(r, mid+1, right);
}

int main() {
    n = 7;
    int r[] = {2, 5, 3, 5, 8, 4, 0};

    search(r, 0, 6);

    return 0;
}
