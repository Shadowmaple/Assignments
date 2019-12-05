/*
课程：C++面向对象程序设计
教师：杨进才
题目：模拟地铁、机场进行危险品检查
要求：输入一个字符串，检查字符串。若其中含有'b''o''m''b'四个字母（字母顺序无关）就抛出异常，提示有炸弹；
     若其中含有'9''1''1'三个数字（数字顺序无关）则抛出异常，提示有恐怖危险。
开发环境：Linux
编译器：g++
时间：2019.12.5
*/

# include <iostream>
# include <string>

using namespace std;

class Check {
private:
    string cargo;
    bool HasBomb();         // 炸弹检查
    bool HasTerrorDanger(); // 恐怖主义危险检查

public:
    Check(string cargo) {this->cargo = cargo;};
    ~Check() {};

    void DangerPanic(); // 危险检查，抛出异常
};

// 检查字符串中是否有两个b
bool hasDoubleB(string s) {
    int num = 0;
    for (int i = 0; i < s.length() && num < 3; i++)
        if (s[i] == 'b' || s[i] == 'B') num++;

    return num == 2;
}

// 检查字符串中是否有o
bool hasCharO(string s) {
    for (int i = 0; i < s.length(); i++)
        if (s[i] == 'o' || s[i] == 'O') return true;

    return false;
}

// 检查字符串中是否有m
bool hasCharM(string s) {
    for (int i = 0; i < s.length(); i++)
        if (s[i] == 'm' || s[i] == 'M') return true;

    return false;
}

// 检查字符串中是否有9
bool hasIntNine(string s) {
    for (int i = 0; i < s.length(); i++)
        if (s[i] == '9') return true;

    return false;
}

// 检查字符串中是否有两个1
bool hasDoubleOne(string s) {
    int num = 0;
    for (int i = 0; i < s.length() && num < 3; i++)
        if (s[i] == '1') num++;

    return num == 2;
}

// 检查是否含有炸弹
bool Check::HasBomb() {
    // if (hasDoubleB(cargo) && hasCharO(cargo) && hasCharM(cargo))
    //     return true;
    // return false;

    return hasDoubleB(cargo) && hasCharO(cargo) && hasCharM(cargo);
}

// 检查是否有恐怖主义危险
bool Check::HasTerrorDanger() {
    // if (hasDoubleOne(cargo) && hasIntNine(cargo))
    //     return true;
    // return false;

    return hasDoubleOne(cargo) && hasIntNine(cargo);
}

// 危险检查，抛出异常
void Check::DangerPanic() {
    bool bomb = HasBomb();
    bool terrorDanger = HasTerrorDanger();

    if (bomb && terrorDanger)
        throw "Has bomb and has 911 terror danger!";
    else if (bomb)
        throw "Has bomb!";
    else if (terrorDanger)
        throw "Has 911 terror danger!";
}

int main() {
    string cargo;
    cout << "Please enter a string：";
    cin >> cargo;

    Check CheckOnce(cargo);

    try {
        CheckOnce.DangerPanic();
        cout << "Check success. No danger." << endl;
    } catch (const char* msg) {
        cout << msg << endl;
    }
    cout << "Check finished." << endl;

    return 0;
}
