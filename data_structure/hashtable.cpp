# include <iostream>
using namespace std;

# define HASHSIZE 16

// 解决冲突
int HI(int i) {
    return (i + 1) % HASHSIZE;
}

int hashsearch(int *hashtable, int key, int *p, int (*cp)(int)) {
    int n = key % 13, cout = 0;
    while (hashtable[n] != 0) {
        n = cp(n);
        cout++;
        // 查找失败
        if (cout > HASHSIZE) return 0;
    }
    // hashtable[n] = key;
    *p = n;
    return 1;
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
    createHashTable(hashtable, num, 12);
    display(hashtable);

    return 0;
}
