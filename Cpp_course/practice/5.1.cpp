# include <iostream>
# include <cmath>
using namespace std;

class Ctriangle {
private:
    float a, b, c;
public:
    Ctriangle(float a, float b, float c) {
        this->a = a;
        this->b = b;
        this->c = c;
    };
    float perimeter() {return a + b + c;};
    float area() {
        // 海伦公式
        float p = perimeter() / 2;
        return sqrt(p * (p - a) * (p - b) * (p - c));
    };
};

int main() {
    Ctriangle triangle(3, 4, 5);
    cout << triangle.perimeter() << endl;
    cout << triangle.area() << endl;
    return 0;
}