
# include "iostream"

using namespace std;

char *add(char *a, char *b, char *c) {
    cout << "(int, int)" << endl;
    char *x = c;
    while (*a != '\0') {
        *c = *a;
        a++;
        c++;
    }
    while (*b != '\0') {
        *c = *b;
        c++;
        b++;
    }
    *c = '\0';
    // c = x;
    return x;
}

int main() {
    char a[] = "sdfsdf", b[] = "ddddd";
    char c[100];
    cout << add(a, b, c) << endl;
    return 0;
}