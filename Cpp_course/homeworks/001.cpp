// 课程：C++面向对象程序设计
// 题目：
// 设计多个重载函数add,进行两个int,float,double数相加，char与int相加，两个字符串相连，返回相应的数。
// 参数传递用传值与传引用方式。
//
// 开发环境：Linux
// 时间：2019.9.19

# include "iostream"
# include "cstring"

using namespace std;

int add(int a, int b) {
    cout << "(int, int)" << endl;
    return a + b;
}

char add(char a, int b) {
    cout << "(char, int)" << endl;
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

char *add(char *a, char *b){
    cout << "(char, char)" << endl;
    strcat(a, b);
    return a;
}

int main() {
    // 整型相加
    int x = 2, y = 3;
    int &k = x, &i = y;
    cout << add(x, y) << endl;  // 传值方式进行整型相加
    cout << add(k, i) << endl;  // 传引用方式进行整型相加

    // char和int相加
    char c1 = 'x';
    char &c2 = c1;
    cout << add(c1, x) << endl; // 传值方式
    cout << add(c2, k) << endl; // 传引用方式

    // float相加
    float f1 = 101.23, f2 = 12.223;
    float & fx = f1, fy = f2;
    cout << add(f1, f2) << endl;    // 传值
    cout << add(fx, fy) << endl;    // 传引用

    // double相加
    double d1 = 24.44444, d2 = 83.422423;
    double & dx = d1, dy = d2;
    cout << add(d1, d2) << endl;    // 传值
    cout << add(dx, dy) << endl;    // 传引用

    // 字符串相连
    char a[] = "hello, world ", b[] = "and c++";
    cout << add(a, b) << endl;

    return 0;
}
