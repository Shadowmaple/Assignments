# include <iostream>
using namespace std;

int main() {
    int stairs[41] = {0, 1, 2};
    for (int i = 3; i <= 41; i++) {
        stairs[i] = stairs[i-1] + stairs[i-2];
    }

    cout << stairs[40] << endl;

    return 0;
}