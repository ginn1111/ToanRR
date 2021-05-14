#pragma once
#include <fstream>
#define MAXSIZE 101

using namespace std;

struct Canh {
	int dau;
	int cuoi;
};

struct ListCanh {
	int n = 0;
	Canh node[MAXSIZE];
};

struct List {
	int n = 0;
	int node[MAXSIZE];
};

struct Stack {
	int sp = -1;
	int p[MAXSIZE];
};

struct Queue {
	int front = -1;
	int rear;
	int p[MAXSIZE];
};

Canh newCanh(int dau, int cuoi) {
	Canh canh;
	canh.dau = dau;
	canh.cuoi = cuoi;
	return canh;
}

void addCanh(ListCanh &ls, Canh canh) {
	if(ls.n == MAXSIZE - 1) {
		cout << "LIST IS FULL!\n";
		return;
	}
	ls.node[ls.n++] = canh;
}

void addList(List &list, int x) {
	if(list.n == MAXSIZE - 1) {
		cout << "LIST IS FULL!\n";
		return;
	}
	list.node[list.n++] = x;
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
	x = st.p[st.sp--];
}

void push_queue(Queue &q, int x) {
	if(q.rear - q.front + 1 == 0 || q.rear - q.front + 1 == MAXSIZE) {
		cout << "QUEUE IS FULL!\n";
		return;
	}
	if(q.front == -1) {
		q.front = 0;
		q.rear = -1;
	}
	if(q.rear + 1 == MAXSIZE) q.rear = -1;
	q.p[++(q.rear)] = x;
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
		if(++(q.front) == MAXSIZE) q.front = 0;
	}
}

void init(char *fileName, int x[][MAXSIZE], int &n, int check[]) {
	fstream f(fileName, ios::in);
	if(f.fail()) {
		cout << "File loi!\n";
		return;
	}
	f >> n;
	for(int i = 1; i <= n; i++) {
		check[i] = 1;
		for(int j = 1; j <= n; j++) {
			f >> x[i][j];
		}
	}
}


