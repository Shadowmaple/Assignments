# include <iostream>
using namespace std;

# define HASHSIZE 16

// 哈希函数
int HO(int key) {
    return key % 13;
}

// 解决冲突
int HI(int i) {
    return (i + 1) % HASHSIZE;
}

void createHashTable(int *hashtable, int *num, int sum) {
    // hashtable = new int(0);
    for (int i = 0; i < sum; i++) {
        int n = HO(num[i]);
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
    createHashTable(hashtable, num, 12);
    display(hashtable);

    return 0;
}
