#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
int board[100][100];
int n,cache[100][100];

int y_n(int x, int y) {
	if (x >= n || y >= n)
		return 0;
	if (x == n - 1 && y == n - 1)
		return 1;
	int& ret = cache[x][y];
	if (ret != -1)
		return ret;
	int dis = board[x][y];
	return ret=(y_n(x + dis, y) || y_n(x, y + dis));//참조형의 변환
}
//재귀 호출 알고리즘
bool jump(int y, int x) {
	if (y >= n || x >= n)
		return false;
	if (y == n - 1 && x == n - 1)
		return true;
	int jumpsize = board[y][x];
	return jump(y + jumpsize, x) || jump(y, x + jumpsize);
}
//동적 계획법 알고리즘
int jump2(int y, int x) {
	if (y >= n || x >= n)
		return 0;
	if (y == n - 1 && x == n - 1)
		return 1;
	int& ret = cache[y][x];
	if (ret != -1)
		return ret;
	int jumpsize = board[y][x];
	return ret = (jump2(y + jumpsize, x) || jump2(y, x + jumpsize));
}
int main(void) {
	int C;
	int i,j,k;
	cin >> C;
	for (i = 0; i < C; i++) {
		memset(cache, -1, sizeof(cache));
		cin >> n;
		for (j = 0; j < n; j++) {
			for (k = 0; k < n; k++) {
				cin>>board[j][k];
			}
		}
		if (y_n(0, 0)) {
			cout << "YES" << endl;
		}
		else
			cout <<"NO"<<endl;
	}
}
