// 三路快排

# include <stdio.h>

void swap(int *x, int *y) {
    int z = *x;
    *x = *y;
    *y = z;
}

void quickSort(int *num, int left, int right) {
    if (left >= right) return ;

    int i = left, j = right, mid = left;
    int key = num[i];
    while (mid <= j) {
        if (num[mid] < key) {
            swap(&num[mid], &num[i]);
            i++;
            mid++;
        } else if (num[mid] > key) {
            swap(&num[mid], &num[j]);
            j--;
        } else
            mid++;
    }
    quickSort(num, left, i - 1);
    quickSort(num, j + 1, right);
}

int mnumin() {
    int num[] = {42, 12, 3, 3, 8, 11, 9, 9};
    quickSort(num, 0, 7);

    for (int i = 0; i < 8; i++)
        printf("%d%c", num[i], i==7 ? '\n':' ');

    return 0;
}