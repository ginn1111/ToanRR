#include<iostream>
using namespace std;

int Y[6] = {-1, 2, 1, 3, 1, 4};
int X[6];
int n = 5;
int m = 3;
int M = 6;



void genaration(int k, int index) {
    for(int i = index; i <= n; i++) {
        X[k] = i;
        if(k == m) {
            for(int i = 1; i <= m; i++) {
                cout << X[i] << " ";
            }
            cout << endl;
        } else {
            genaration(k + 1, i + 1);
        }
    }
}

int main() {
    genaration(1,1);
    return 0;
}

/*
void checkANDresult() {
    int sum = 0;
    for(int i = 1; i <= m; i++) {
        sum += X[i];
    }
    if(sum == M) {
        for(int i = 1; i <= m; i++) {
            cout << X[i] << " ";
        }
        cout << endl;
    }
}
*/