#include <iostream>
#include <fstream>
#define MAXSIZE 100

using namespace std;

int chuaxet[MAXSIZE];

struct Stack {
	int sp = -1;
	int p[MAXSIZE];
};

void push_stack(Stack &st, int x) {
	if(st.sp == MAXSIZE - 1) {
		cout << "STACK IS FULL!\n";
		return;
	}
	st.p[++(st.sp)] = x;
}

void pop_stack(Stack &st, int &x) {
	if(st.sp == -1) {
		cout << "STACK IS EMPTY!\n";
		return;
	}
	x = st.p[(st.sp)--];
}

void init(int x[], int head[], int &n) {
	fstream f("input.in", ios::in);
	if(f.fail()) {
		cout << "FILE LOI!\n";
		return;
	}
	f >> n;
	for(int i = 1; i <= n; i++) {
		f >> head[i];
		chuaxet[i] = 1;
		for(int j = head[i - 1]; j < head[i]; j++) {
			f >> x[j];
		}
	}
}

void DFS(int u, int head[], int x[], int n) {
	chuaxet[u] = 0;
	for(int i = head[u - 1]; i < head[u]; i++) {
		if(chuaxet[x[i]]){
			cout << x[i] << " ";
			DFS(x[i], head, x, n);
		}
	}
}

void DFS_Stack(int u, int head[], int x[], int n) {
	Stack st;
	
	int s;
	push_stack(st, u);
	chuaxet[u] = 0;
	cout << u << " ";
	while(st.sp != -1) {
		pop_stack(st, s);
		for(int i = head[s - 1]; i < head[s]; i++) {
			if(chuaxet[x[i]]) {
				chuaxet[x[i]] = 0;
				push_stack(st, s);
				push_stack(st, x[i]);
				cout << x[i] << " ";
				break;
			}
		}
	}
}

void timCacThanhPhanLienThong(int x[], int head[], int n) {
	int stplt = 0;
	for(int i = 1; i <= n; i++) {
		if(chuaxet[i]) {
			stplt++;
			cout << "SO THANH PHAN LIEN THONG THU: " << stplt << ": ";
			DFS_Stack(i, head, x, n);
			cout << endl;
		}
	}
}

void xuatCacDinhKe(int x[], int head[], int k, int n) {
	for(int i = 1; i <= n; i++) {
		cout << "Cac dinh ke voi dinh " << i << ": ";
		for(int j = head[i - 1]; j < head[i]; j++) {
			cout << x[j] << " ";
		}
		cout << endl;
	}
}

int main() {
	int x[MAXSIZE], head[MAXSIZE], n, k;
	head[0] = 0;
	init(x, head, n);
	k = head[n] - 1;
	DFS_Stack(1, head, x, n);
	
	return 0;
}
