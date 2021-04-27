#include <iostream>
#include <fstream>
#define MAXSIZE 100


using namespace std;

int chuaxet[MAXSIZE];

struct Stack {
	int sp = -1;
	int p[MAXSIZE];
};

struct List{
	int n = 0;
	int node[MAXSIZE];
};

void addList(List &list, int x) {
	if(list.n == MAXSIZE) {
		cout << "LIST IS FULL!\n";
		return;
	}
	list.node[list.n++] = x;
}

void push(Stack &st, int x) {
	if(st.sp + 1 == MAXSIZE) {
		cout << "STACK IS FULL!\n";
		return;
	}
	st.p[++(st.sp)] = x;
}

void pop(Stack &st, int &x) {
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

int DFS_Stack(int x[][MAXSIZE], int n, int u) {
	Stack st;
	push(st, u);
	chuaxet[u] = 0;
	int s, cnt = 1;
	while(st.sp != -1) {
		pop(st, s);
		for(int i = 1; i <= n; i++) {
			if(x[s][i] && chuaxet[i]) {
				push(st, s);
				push(st, i);
				chuaxet[i] = 0;
				cnt++;
				break;
			}
		}
	}
	return cnt;
}

bool kiemTraEuler(int x[][MAXSIZE], int n) {
	int cnt;
	for(int i = 1; i <= n; i++) {
		cnt = 0;
		for(int j = 1; j <= n; j++) {
			cnt += x[i][j];
		}
		if(cnt % 2 != 0) return false;
	}
	for(int i = 1; i <= n; i++) {
		if(DFS_Stack(x, n, i) == n) return true;
	}
	return false;
}

/*
	Theo thuat toan Flor, chon dinh di bat ky tuan thu 2 quy tac
		1. Bo cac canh da di qua, dong thoi bo luon cac dinh co lap
		2. Uu tien di qua cac canh khong phai la cau
*/

void chuTrinhEuler(int x[][MAXSIZE], int n, int u, List &list) {
	if(!kiemTraEuler(x, n)) {
		cout << "DO THI KHONG PHAI LA DO THI EULER!\n";
		return;
	}
	Stack st;
	push(st, u);
	int s;
	bool kt;
	while(st.sp != -1) {
		kt = false;
		pop(st, s);
		for(int i = 1; i <= n; i++) {
			if(x[s][i]) {
				kt = true;
				push(st, s);
				push(st, i);
				x[s][i] = 0;
				x[i][s] = 0;
				break;
			}
		}
		if(!kt) {
			addList(list, s);
		}
	}
}

void xuatMang(int x[][MAXSIZE], int n) {
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= n; j++ ){
			cout << x[i][j] << " ";
		}
		cout << endl;
	}
}

void chuTrinhHamilton(int x[][MAXSIZE], int n, int k, int res[], int v0) {
	for(int i = 1; i <= n; i++) {
		if(x[res[k - 1]][i]) {
			if(k == n + 1 && i == v0) {
			res[k] = v0;
			for(int j = 1; j <= n + 1; j++) {
				cout << res[j] << " ";
			}
			cout << endl;
			} else if(chuaxet[i]) {
				res[k] = i;
				chuaxet[i] = 0;
				chuTrinhHamilton(x, n, k + 1, res, v0);
				chuaxet[i] = 1;
			}
		}
	}
}

void capNhatPhuongAn(int res[], int n, int &fopt, int x[][MAXSIZE], int xopt[]) {
	int sum = 0;
	for(int i = 1; i <= n; i++) {
		cout << x[res[i]][res[i + 1]] << endl;
		system("pause");
		sum += x[res[i]][res[i + 1]];
	}
	if(sum < fopt) {
		fopt = sum;
		for(int i = 1; i <= n + 1; i++) {
			xopt[i] = res[i];
		}
	}
}

void nguoiDiDuLich(int x[][MAXSIZE], int n, int k, int tmp[], int v0, int &fopt, int xopt[]) {
	for(int i = 1; i <= n; i++) {
		if(x[tmp[k - 1]][i] != -1 && x[tmp[k - 1]][i] != 0) {
			if(k == n + 1 && i == v0) {
				tmp[k] = v0;
				capNhatPhuongAn(tmp, n, fopt, x, xopt);
			} else if(chuaxet[i]) {
				tmp[k] = i;
				chuaxet[i] = 0;
				nguoiDiDuLich(x, n, k + 1, tmp, v0, fopt, xopt);
				chuaxet[i] = 1;
			}
		}
	}
}

int main() {
	int x[MAXSIZE][MAXSIZE], n;
	int tmp[MAXSIZE],  xopt[MAXSIZE];
	init(x, n);
//	List list;
//	chuTrinhEuler(x, n, 1, list);
//	for(int i = list.n - 1; i >= 0; i--) {
//		cout << list.node[i] << " ";
//	}

//	xuatMang(x, n);
	tmp[1] = 1;
	int fopt = 9999;
	chuaxet[tmp[1]] = 0;
	cout << n << endl;
	nguoiDiDuLich(x, n, 2, tmp, tmp[1], fopt, xopt);
	for(int i = 1; i <= n + 1; i++) 
		cout << xopt[i] << " ";
	cout << endl << "CHI PHI: " << fopt << endl;
	return 0;
}
