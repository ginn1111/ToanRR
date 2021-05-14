#include <iostream>
#include "mylib.h"

using namespace std;

int check[MAXSIZE];
int x[MAXSIZE][MAXSIZE];
int ketQuaHamilton[MAXSIZE];
int n;
int fopt = 99999;
int xopt[MAXSIZE];
int tmp[MAXSIZE];
List ketQuaEuler;
ListCanh ketQuaCayKhung;

void DFS(int u) {
	Stack st;
	push_stack(st, u);
	check[u] = 0;
	int s;
	cout << u << " ";
	while(st.sp != -1) {
		pop_stack(st, s);
		for(int i = 1; i <= n; i++) {
			if(x[s][i] && check[i]) {
				push_stack(st, s);
				push_stack(st, i);
				check[i] = 0;
				cout << i << " ";
				break;
			}
		}
	}
}

void BFS(int u) {
	Queue q;
	push_queue(q, u);
	check[u] = 0;
	cout << u << " ";
	int s;
	while(q.front != -1) {
		pop_queue(q, s);
		for(int i = 1; i <= n; i++) {
			if(x[s][i] && check[i]) {
				push_queue(q, i);
				check[i] = 0;
				cout << i << " ";
			}
		}
	}
}

int duyetThanhPhanLienThong() {
	int stplt = 0;
	for(int i = 1; i <= n; i++) {
		if(check[i]) {
			stplt++;
			DFS(i);
		}
	}
	return stplt;
}

bool kiemTraDoThiEuler() {
	int cnt;
	for(int i = 1; i <= n; i++) {
		cnt = 0;
		for(int j = 1; j <= n; j++) {
			cnt += x[i][j];
		}
		if(cnt % 2 != 0) return false;
	}
	if(duyetThanhPhanLienThong() == 1) return true;
	return false;
}

void chuTrinhEuler(int u) {
	if(!kiemTraDoThiEuler()) {
		cout << "DO THI KHONG PHAI LA DO THI EULER!\n";
		return;
	}
	Stack st;
	push_stack(st, u);
	int s;
	bool kt;
	while(st.sp != -1) {
		kt = false;
		pop_stack(st, s);
		for(int i = 1; i <= n; i++) {
			if(x[s][i]) {
				kt = true;
				push_stack(st, s);
				push_stack(st, i);
				x[s][i] = 0;
				x[i][s] = 0;
				break;
			}
		}
		if(!kt) addList(ketQuaEuler, s);
	}
	for(int i = ketQuaEuler.n - 1; i >= 0; i--)
		cout << ketQuaEuler.node[i] << " ";
	cout << endl;
}

void Try(int k, int v0) {
	for(int i = 1; i <= n; i++) {
		if(x[ketQuaHamilton[k - 1]][i]) {
			if(k == n + 1 && i == v0) {
				ketQuaHamilton[k] = i;
				for(int j = 1; j <= k; j++)
					cout << ketQuaHamilton[j] << " ";
				cout << endl;
			}
			else if(check[i]){
				ketQuaHamilton[k] = i;
				check[i] = 0;
				Try(k + 1, v0);
				check[i] = 1;
			}
		}
	}
}

void chuTrinhHamilton() {
	ketQuaHamilton[1] = 1;
	check[1] = 0;
	Try(2, ketQuaHamilton[1]);
}

void xuatMang(int x[][MAXSIZE], int n) {
	for(int i = 1; i <= n; i++) {
		for(int j = 1; j <= n; j++)
			cout << x[i][j] << " ";
		cout << endl;
	}
}

void timCayKhungCuaDoThi(int u) {
	Queue q;
	push_queue(q, u);
	check[u] = 0;
	int s;
	while(q.front != -1) {
		pop_queue(q, s);
		for(int i = 1; i <= n; i++) {
			if(x[s][i] && check[i]) {
				push_queue(q, i);
				check[i] = 0;
				addCanh(ketQuaCayKhung, newCanh(s, i));
			}
		}
	}
}

void xuatCayKhung(int u) {
	timCayKhungCuaDoThi(u);
	if(ketQuaCayKhung.n < n - 1) {
		cout << "DO THI KHONG LIEN THONG!\n";
		return;
	}
	for(int i = 0; i < ketQuaCayKhung.n; i++) {
		cout << "(" << ketQuaCayKhung.node[i].dau << ", " << ketQuaCayKhung.node[i].cuoi << ")";
		if(i + 1 != ketQuaCayKhung.n) cout << "; ";
	}
}

void capNhatPhuongAn() {
	int sum = 0;
	for(int i = 1; i <= n; i++)
		sum += x[tmp[i]][tmp[i + 1]];
	if(fopt > sum) {
		fopt = sum;
		for(int i = 1; i <= n + 1; i++)
			xopt[i] = tmp[i];
	}
}

void TryNDDL(int k, int v0) {
	for(int i = 1; i <= n; i++) {
		if(x[tmp[k - 1]][i] != -1 && x[tmp[k - 1]][i] != 0) {
			if(k == n + 1 && i == v0) {
				tmp[k] = i;
				capNhatPhuongAn();
			} else if(check[i]) {
				tmp[k] = i;
				check[i] = 0;
				TryNDDL(k + 1, v0);
				check[i] = 1;
			}
		}
	}
}

void nguoiDiDuLich() {
	tmp[1] = 1;
	check[1] = 0;
	TryNDDL(2, tmp[1]);
	cout << "PHUONG AN: ";
	for(int i = 1; i <= n + 1; i++)
		cout << xopt[i] << " ";
	cout << "\nCHI PHI: " << fopt;
}

int main() {
	char fileName[] = "nguoididulich.txt";
	init(fileName,x,n,check);
	nguoiDiDuLich();
	return 0;
}
