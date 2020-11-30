#include<iostream>
#include<fstream>
#define INFINITY 99999
#define MAX 100
using namespace std;

int cmin = INFINITY;
int fopt = INFINITY;
int maTrixCost[MAX][MAX];
int xopt[MAX];
int check[MAX];
int X[MAX];
int cost;

void init() {
    fstream input("D:\\IT\\C++\\ToanRR\\input.txt", ios::in);
    if(input.fail()) {
        cout << "File is not open!";
        exit(1);
    }
    for(int i = 1; i <= 5; i++) {
        for(int j = 1; j <= 5; j++) {
            input >> maTrixCost[i][j];
        }
    }

    cout << "MA TRAN:\n";
    for(int i = 1; i <= 5; i++) {
        for(int j = 1; j <= 5; j++) {
            printf("%5d", maTrixCost[i][j]);
        }
        cout << endl;
    }
}

void cminInMatrix() {
    for(int i = 1; i <= 5; i++) {
        for(int j = 1; j <= 5; j++) {
            if(i != j) {
                cmin = min(cmin, maTrixCost[i][j]);
            }
        }
    }
}

void update() {
    int sum = cost + maTrixCost[X[5]][X[1]];
    if(fopt > sum) {
        fopt = sum;
        for(int i = 1; i <= 5; i++) {
            xopt[i] = X[i];
        }
    }
}

void result() {
    for(int i = 1; i <= 5; i++) {
            cout << xopt[i] << " ";
    }
}

void Try(int k) {
    for(int i = 2 ; i <= 5; i++) {
        if(!check[i]) {
            check[i] = 1;
            X[k] = i;
            cost += maTrixCost[X[k - 1]][X[k]];
            if(k == 5) {
                update();
            } else if(cost + (5 - k + 1)*cmin <= fopt) {
                Try(k + 1);
            }
            check[i] = 0;
            cost -= maTrixCost[X[k - 1]][X[k]];
        }
    }
}

int main() {
    X[1] = 1;
    check[1] = 1;
    init();
    cminInMatrix();
    cout << endl << cmin << endl;
    Try(2);
    result();
    return 0;
}