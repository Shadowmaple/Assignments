/*******************************************************************
题目：
给定一个整型序列作为关键字，利用哈希函数H0(key)=key%13为其构造哈希表，
利用函数Hi=(Hi+1)%HASHSIZE，i=1,2,…处理冲突，输出哈希表元素值以及对应的地址。
********************************************************************/

# include <iostream>
using namespace std;

# define HASHSIZE 16

// 解决冲突，线性探测
int HI(int i) {
    return (i + 1) % HASHSIZE;
}

int hashsearch(int *hashtable, int key, int *p, int (*cp)(int)) {
    int n = key % 13, count = 0;
    while (hashtable[n] != 0) {
        n = cp(n);
        // 线性探测次数
        count++;
        // 查找失败
        if (count > HASHSIZE) return 0;
    }
    // hashtable[n] = key;
    *p = n;
    return 1;
}

void createHashTable_v2(int *hashtable, int *num, int sum) {
    for (int i = 0; i < sum; i++) {
        int p = -1; // 查找到的索引
        if (hashsearch(hashtable, num[i], &p, HI)) {
            hashtable[p] = num[i];
            cout << num[i] << " 查找成功" << endl;
        } else {
            // 需要扩容...
            hashtable = new int(HASHSIZE * 2);
            cout << num[i] << " 查找失败" << endl;
        }
    }
}

void createHashTable(int *hashtable, int *num, int sum) {
    for (int i = 0; i < sum; i++) {
        int n = num[i] % 13;
        while (hashtable[n] != 0) {
            n = HI(n);
        }
        hashtable[n] = num[i];
    }
}

void display(int *hashtable) {
    for (int i = 0; i < HASHSIZE; i++)
        cout << i << ' ' << hashtable[i] << endl;
}

int main() {
    int num[12] = {19, 14, 23, 1, 68, 20, 84, 27, 55, 11, 10, 79};
    int hashtable[HASHSIZE] = {0};
    // createHashTable(hashtable, num, 12);
    createHashTable_v2(hashtable, num, 12);
    display(hashtable);

    return 0;
}
