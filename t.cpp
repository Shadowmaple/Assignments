# include <iostream>
# include <unistd.h>
# include <time.h>
using namespace std;

int main() {
    for (int i = 0; i < 100; i++) {
        printf("\r%d", i);
        fflush(stdout);
        sleep(1);
    }
    return 0;
}