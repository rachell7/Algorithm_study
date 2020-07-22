#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
char board[20][20];
int H, W;//H:줄(행) W:글자(열)
int l[4][3] = { { 0,1,1 } ,{ 0,-1,1 } ,{ 0,-1,-1 } ,{ 0,1,-1 } };//현 위치, 열이동, 행이동
bool check(char board[20][20]) {
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			if (board[i][j] == '.')
				return false;
		}
	}
	return true;
}
int fill(int block) {
	int i, j,k;
	int sum=0;
	if (block==0&&check(board)) {
		return 1;
	}
	for (i = 0; i < H; i++) {//범위 내
		for (j = 0; j < W; j++) {
			if (board[i][j] == '.') {
				for (k = 0; k < 4; k++) {
					if (j+l[k][1]>0 && j+l[k][1]<W && i + l[k][2] >0 && i+l[k][2] <H &&board[i][j + l[k][1]] == '.' && board[i + l[k][2]][j] == '.') {
						board[i][j] = board[i][j + l[k][1]] = board[i + l[k][2]][j] = 'l';
						sum+=fill(block-1);
						board[i][j] = board[i][j + l[k][1]] = board[i + l[k][2]][j] = '.';
					}
				}
				
			}
		}
	}
	return sum;
}
int main() {
	int C;//C:테스트 케이스의 수
	int i;
	int r, c;
	int avail = 0;
	int way = 0;
	cin >> C;
	for (i = 0; i < C; i++) {
		avail = 0;
		cin >> H >> W;
		for (r = 0; r < H; r++) {
			for (c = 0; c < W; c++) {
				cin >> board[r][c];//'#':검은 칸 '.':흰 칸
				if (board[r][c] == '.') {
					avail += 1;
				}
			}
		}
		if (avail % 3 == 0) {
			way=fill(avail / 3);
		}
		else {
			way = 0;
		}
		cout << way << endl;
		memset(board, 'X', sizeof(board));
	}
}



using namespace std;
int H, W;
const int coverType[4][3][2] = { {{0,0},{1,0},{0,1}},{{0,0},{0,1},{1,1}},{{0,0},{1,0},{1,1}},{{0,0},{1,0},{1,-1}} };
vector<vector<int>> board;
bool set(vector <vector<int>>& board, int y, int x, int type, int delta) {
	bool ok = true;
	for (int i = 0; i < 3; i++) {
		const int ny = y + coverType[type][i][0];
		const int nx = x + coverType[type][i][1];
		if (ny < 0 || ny >= board.size() || nx < 0 || nx >= board[0].size())
			ok = false;
		else if ((board[ny][nx] += delta) > 1)//
			ok = false;
	}
	return ok;
}
int cover(vector<vector<int>>& board) {
	int y = -1, x = -1;
	for (int i = 0; i < board.size(); i++) {
		for (int j = 0; j < board[i].size(); j++) {
			if (board[i][j] == 0) {//가장 위, 왼쪽 흰 칸
				y = i;
				x = j;
				break;
			}
		}
		if (y != -1) {
			break;
		}
	}
	if (y == -1) {
		return 1;
	}
	int ret = 0;
	for (int type = 0; type < 4; type++) {
		if (set(board, y, x, type, 1)) {
			ret += cover(board);
		}
		set(board, y, x, type, -1);//수거
	}
	return ret;
}
int main(void) {
	int C;
	char a;
	int way = 0;
	int sum = 0;
	cin >> C;
	for (int i = 0; i < C; i++) {
		cin >> H >> W;
		sum = 0;
		for (int r = 0; r < H; r++) {
			board.push_back(vector<int>(W));
			for (int c = 0; c < W; c++) {
				cin >> a;
				if (a == '.') {
					board[r][c] = 0;
					sum += 1;
				}
				else if (a == '#') {
					board[r][c] = 1;
				}
			}
		
		}
		if (sum % 3 == 0) {
			way = cover(board);
		}
		else {
			way = 0;
		}
		cout << way << endl;
		board.clear();
	}
	
	
}