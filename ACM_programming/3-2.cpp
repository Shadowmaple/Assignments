# include <iostream>
# include <map>
# include <cstring>
using namespace std;

int main() {
    char s[150];
    map<char, char> mapChar;
    char mirror[] = "A   3  HIL JM O   2TUVWXY51SE Z  8 ";
    char chs[] = "ABCDEFGHIGKLMNOPQRSTUVWXYZ123456789";
    for (int i = 0; i < strlen(chs)-1; i++)
        mapChar[chs[i]] = mirror[i];

    while(scanf("%s", s) != EOF) {
        bool pal = true, mir = true;
        for (int i = 0, j = strlen(s)-1; i < j; i++, j--) {
            if (s[i] == 'O' && s[j] == '0' || s[i] == '0' && s[j] == 'O') continue;
            if (s[i] != s[j]) pal = false;

            if (s[i] != mapChar[s[j]])
                mir = false;
        }
        if (pal && mir)
            cout << s << " -- is a mirrored palindrome.\n\n";
        else if (pal)
            cout << s << " -- is a regular palindrome.\n\n";
        else if (mir)
            cout << s << " -- is a mirrored string.\n\n";
        else
            cout << s << " -- is not a palindrome.\n\n";
    }
    return 0;
}