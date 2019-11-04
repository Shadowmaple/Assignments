# include <iostream>
using namespace std;

struct SingelLink {
    int column;
    int value;
    SingelLink *next;
};

struct LinkMatrix {
    SingelLink *link;
};

void createLinkMatrix(LinkMatrix *matrix, int *num, int row, int column) {
    for (int i = 0; i < row; i++) {
        SingelLink *currentLink = matrix[i].link;
        currentLink = NULL;

        for (int j = 0; j < column; j++) {
            int x = i * column + j;
            if (!num[x]) continue;
            SingelLink *link = new SingelLink{j, num[x], NULL};
            if (currentLink == nullptr) {
                matrix[i].link = link;
                currentLink = link;
                continue;
            }
            currentLink->next = link;
            currentLink = currentLink->next;
        }
    }
}

void displayLinkMatrix(LinkMatrix *matrix, int row) {
    for (int i = 0; i < row; i++) {
        cout << i;
        SingelLink *link = matrix[i].link;
        while (link) {
            printf("\t%d, %d", link->column, link->value);
            link = link->next;
        }
        cout << '\n';
    }
}

int main() {
    int num[25] = {3, 0, 0, 0, 7,
                    0, 0, -1, 0, 0,
                    -1, -2, 0, 0, 0,
                    0, 0, 0, 0, 0,
                    0, 0, 0, 2, 0};
    LinkMatrix matrix[5];
    createLinkMatrix(matrix, num, 5, 5);
    displayLinkMatrix(matrix, 5);

    return 0;
}
