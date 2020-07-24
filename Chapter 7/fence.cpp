#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;
vector <int> fence;
int max_square(vector <int>& f) {
	int i, j;
	int h = 0, w = 0;
	int p = 0;
	for (i = 0; i < f.size(); i++) {
		h = f[i];
		for (j = i; j < f.size(); j++) {
			if (h > f[j]) {
				h = f[j];
			}
			p = h * (j - i + 1);
			if (p > w) {
				w = p;
			}
		}
	}
	return w;
}
int solve(int l, int r) {
	if (l == r) {
		return fence[l];
	}
	int mid = (l + r) / 2;
	int ret = max(solve(l, mid), solve(mid + 1, r));
	int lr = mid, rl = mid + 1;
	int height = min(fence[lr], fence[rl]);
	ret = max(ret, 2 * height);
	while (l < lr || rl < r) {
		if (rl < r && (lr == l || fence[lr - 1] < fence[rl + 1])) {
			++rl;
			height = min(height, fence[rl]);
		}
		else {
			--lr;
			height = min(height, fence[lr]);
		}
		ret = max(ret, height * (rl - lr + 1));
	}
	return ret;
}
int main(void) {

	int C;
	int N;
	int h;
	cin >> C;
	for (int i = 0; i < C; i++) {
		cin >> N;
		for (int j = 0; j < N; j++) {
			cin >> h;
			fence.push_back(h);
		}
		cout<<solve(0,N-1)<<endl;
		fence.clear();
	}
}