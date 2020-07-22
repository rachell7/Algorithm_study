/*
#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#define MAX_NUM 1048576;
using namespace std;
int link_switch[10][16] = { {3,3,3,0,0,0,0,0,0,0,0,0,0,0,0,0},{0,0,0,3,0,0,0,3,0,3,0,3,0,0,0,0},{0,0,0,0,3,0,0,0,0,0,3,0,0,0,3,3},{3,0,0,0,3,3,3,3,0,0,0,0,0,0,0,0},{0,0,0,0,0,0,3,3,3,0,3,0,3,0,0,0},{3,0,3,0,0,0,0,0,0,0,0,0,0,0,3,3},{0,0,0,3,0,0,0,0,0,0,0,0,0,0,3,3},{0,0,0,0,3,3,0,3,0,0,0,0,0,0,3,3}, {0,3,3,3,3,3,0,0,0,0,0,0,0,0,0,0},{0,0,0,3,3,3,0,0,0,3,0,0,0,3,0,0}};
void next(int clock[], int type) {
	for (int i = 0; i < 16; i++) {
		clock[i]+=link_switch[type][i];
		if (clock[i] == 15) {
			clock[i] = 3;
		}
	}
}

int search(int clock[],int type) {
	int i,j;
	int res = MAX_NUM;
	bool all = true;
	if (type == 10) {
		for (i = 0; i < 16; i++) {
			if (clock[i] != 12) {
				all = false;
				break;
			}
		}
		if (all == false) {
			return MAX_NUM;
		}
		else {
			return 0;
		}
	}
	for (i = 0; i < 4; i++) {
		res = min(res, i + search(clock,type+1));
		next(clock, type);
	}
	return res;
}
int main(void) {
	int C;
	int i,j;
	int w;
	int clock[16];
	cin >> C;
	for (i = 0; i < C; i++) {
		memset(clock, 0, sizeof(clock));
		for (j = 0; j < 16; j++) {
			cin >> clock[j];
		}
		w = search(clock,0);
		if (w == 1048576) {
			cout << -1 << endl;
		}
		else {
			cout << w << endl;
		}
	}
}
*/
#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;
const int INF = 9999, SWITCHES = 10, CLOCKS = 16;
const char linked[SWITCHES][CLOCKS + 1] = {
	"xxx.............",
	"...x...x.x.x....",
	"....x.....x...xx",
	"x...xxxx........",
	"......xxx.x.x...",
	"x.x...........xx",
	"...x..........xx",
	"....xx.x......xx",
	".xxxxx..........",
	"...xxx...x...x.."
};
bool areAligned(const vector<int>& clocks) {
	for (int i = 0; i < 16;i++) {
		if (clocks[i] != 12) {
			return false;
		}
	}
	return true;
}

void push(vector<int>& clocks, int swtch) {
	for (int clock = 0; clock < CLOCKS; ++clock) {
		if (linked[swtch][clock] == 'x') {
			clocks[clock] += 3;
			if (clocks[clock] == 15)
				clocks[clock] = 3;
		}
	}
}
int solve(vector<int>& clocks, int swtch) {
	if (swtch == SWITCHES) {
		return areAligned(clocks) ? 0 : INF;
	}
	int ret = INF;
	for (int cnt = 0; cnt < 4; ++cnt) {
		ret = min(ret, cnt + solve(clocks, swtch + 1));
		push(clocks, swtch);
	}
	return ret;
}
int main(void) {
	int C;
	int w;
	int time;
	vector<int> clocks;
	cin >> C;
	for (int i = 0; i < C; i++) {
		for (int j = 0; j < 16; j++) {
			cin >> time;
			clocks.push_back(time);
		}
		w=solve(clocks, 0);
		if (w == INF) {
			cout << -1 << endl;
		}
		else {
			cout << w << endl;
		}
		clocks.clear();
	}
}