#include <iostream>
#include <fstream>
#define MAXSIZE 100

using namespace std;

int chuaxet[MAXSIZE];

struct Stack {
	int sp = -1;
	int p[MAXSIZE];
};

struct Queue {
	int front = -1;
	int rear;
	int p[MAXSIZE];
};

void push_queue( Queue &q, int x) {
	if(q.rear - q.front + 1 == 0 || q.rear - q.front + 1 == MAXSIZE) {
		cout << "QUEUE IS FULL!\n";
		return;
	}
	if(q.front == -1) {
		q.front = 0;
		q.rear = -1;
	}
	if(q.rear + 1 == MAXSIZE) q.rear = -1;
	q.rear++;
	q.p[q.rear] = x;
}

void pop_queue(Queue &q, int &x) {
	if(q.front == -1) {
		cout << "QUEUE IS EMPTY!\n";
		return;
	}
	x = q.p[q.front];
	if(q.front == q.rear) {
		q.front = -1;
		q.rear = -1;
	} else {
		q.front++;
		if(q.front == MAXSIZE) q.front = 0;
	}
}

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

void init(int x[][MAXSIZE], int &n) {
	fstream f("matranke.txt", ios::in);
	if(f.fail()) {
		cout << "FILE LOI!\n";
		return;
	}
	f >> n;
	for(int i = 1; i <= n; i++) {
		chuaxet[i] = 1;
		for(int j = 1; j <= n; j++) {
			f >> x[i][j];
		}
	}
}

void DFS(int x[][MAXSIZE], int n, int u) {
	chuaxet[u] = 0;
	for(int i = 1; i <= n; i++) {
		if(x[u][i] && chuaxet[i]) {
			cout << i << " ";
			DFS(x, n, i);
		}
	}
}

void DFS_Stack(int x[][MAXSIZE], int n, int u) {
	Stack st;
	push_stack(st, u);
	chuaxet[u] = 0;
	cout << u << " ";
	int s;
	while(st.sp != -1) {
		pop_stack(st, s);
		for(int i = 1; i <= n; i++) {
			if(x[s][i] && chuaxet[i]) {
				chuaxet[i] = 0;
				push_stack(st, s);
				push_stack(st, i);
				cout << i << " ";
				break;
			}
		}
	}
}

void BFS(int x[][MAXSIZE], int n, int u) {
	Queue q;
	push_queue(q, u);
	chuaxet[u] = 0;
	cout << u << " ";
	int s;
	while(q.front != -1) {
		pop_queue(q, s);
		for(int i = 1; i <= n; i++) {
			if(x[s][i] && chuaxet[i]) {
				chuaxet[i] = 0;
				push_queue(q, i);
				cout << i << " ";
			}
		}
	}
}

void xuatMang(int x[][MAXSIZE], int n) {
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= n; j++) {
			cout << x[i][j] << " ";
		}
		cout << endl;
	}
}

int main() {
	int x[MAXSIZE][MAXSIZE];
	int n;
	init(x, n);
//	xuatMang(x, n);
	BFS(x, n, 1);
	return 0;
}
