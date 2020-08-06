#include <iostream>
#include <cstring>
#include <iomanip>
using namespace std;
int n, m;
const int MAX_N = 1001;
double cache[MAX_N][MAX_N];
double climb2(int days, int climbed) {
	if (days == m)
		return climbed >= n ? 1 : 0;
	double& ret = cache[days][climbed];
	if (ret != -1)
		return ret;
	else
		return ret = 0.75 * climb2(days + 1, climbed + 2) + 0.25 * climb2(days + 1, climbed + 1);
}
int main() {
	int C;
	int i;
	cin >> C;
	for (i = 0; i < C; i++) {
		cin >> n >> m;//nπÃ≈Õ m¿œ
		for (int j = 0; j < MAX_N; j++) {
			for (int k = 0; k < MAX_N; k++) {
				cache[j][k] = -1;
			}
		}
		cout << fixed<<setprecision(10)<<climb2(0, 0) << endl;
	}
}