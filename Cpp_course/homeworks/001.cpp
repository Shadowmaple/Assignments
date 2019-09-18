// 题目：
// 设计多个重载函数add,进行两个int,float,double数相加，char与int相加，两个字符串相连，返回相应的数。
// 参数传递用传值与传引用方式。

# include "iostream"
# include "cstring"

using namespace std;

int add(int a, int b) {
    cout << "(int, int)" << endl;
    return a + b;
}

float add(float a, float b) {
    cout << "(float, float)" << endl;
    return a + b;
}

double add(double a, double b) {
    cout << "(double, double)" << endl;
    return a + b;
}

char *add(char *a, char *b) {
    cout << "(char, char)" << endl;
    strcat(a, b);
    return a;
}

int main() {
    int x = 2, y = 3;
    int &k = x, &i = y;
    cout << add(k, i) << endl;

    cout << add(float(101.23), float(12.22)) << endl;
    cout << add(101.23, 12.22) << endl;

    char a[] = "hello, world ", b[] = "and c++";
    cout << add(a, b) << endl;
    return 0;
}
