# include <iostream>
# include <string>
using namespace std;

// 加
string sum(string& num1, string& num2) {
    string result;
    int i = num1.length()-1, j = num2.length()-1;
    int flag = 0, sum;
    for (; i >= 0 && j >= 0; i--, j--) {
        sum = flag + (num1[i] - '0') + (num2[j] - '0');
        flag = sum / 10;
        result = char(sum % 10 + '0') + result;
    }
    while (i >= 0) {
        sum = flag + (num1[i] - '0');
        flag = sum / 10;
        result = char(sum % 10 + '0') + result;
        i--;
    }
    while (j >= 0) {
        sum = flag + (num2[j] - '0');
        flag = sum / 10;
        result = char(sum % 10 + '0') + result;
        j--;
    }
    if (flag) result = char(flag + '0') + result;

    return result;
}

// 乘
string multi(string& num1, int num2) {
    int len = num1.length(), count = 0;
    string result;
    while (num2) {
        int n = num2 % 10;
        int flag = 0;
        string s;
        for (int i = len-1; i >= 0; i--) {
            int sum = n * (num1[i] - '0') + flag;
            flag = sum / 10;
            s = char(sum % 10 + '0') + s;
        }
        if (flag) s = char(flag + '0') + s;

        for (int i = 0; i < count; i++) s += '0';

        if (result == "") result = s;
        else result = sum(result, s);

        num2 /= 10;
        count++;
    }
    return result;
}

int main() {
    int n;
    cin >> n;
    string result = "1";
    int num = 1;
    for (int i = 2; i <= n; i++) {
        num *= i;
        if (num > 3000) {
            result = multi(result, num);
            num = 1;
        }
    }
    if (num > 1) result = multi(result, num);

    cout << result << endl;
    return 0;
}