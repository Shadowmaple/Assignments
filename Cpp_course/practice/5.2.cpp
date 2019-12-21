# include <iostream>
# include <cmath>
using namespace std;

class Point {
private:
    double x, y;
public:
    Point(double x, double y) {
        this->x = x;
        this->y = y;
    };
    double Distance(const Point &p) {
        double a = x - p.x, b = y - p.y;
        return sqrt(a * a + b * b);
    };
};

int main() {
    Point a(1, 2), b(3, 4);
    cout << a.Distance(b) << endl;

    return 0;
}