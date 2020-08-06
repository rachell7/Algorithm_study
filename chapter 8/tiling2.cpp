//#include <iostream>
//#include <algorithm>
//#include <cstring>
//using namespace std;
//int cache[101];
//int sum(int n) {
//	if (n <= 1)
//		return 1;
//	int& ret = cache[n];
//	if (ret != -1)
//		return ret;
//	return ret = (sum(n - 1) + sum(n - 2))% 1000000007;
//}
//int main() {
//	int C;
//	int i;
//	int n;
//	cin >> C;
//	for (i = 0; i < C; i++) {
//		memset(cache, -1, sizeof(cache));
//		cin >> n;
//		cout << sum(n) << endl;
//	}
//}
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
const int MOD = 1000000007;
int cache[101];
int tiling(int width) {
	if (width <= 1)
		return 1;
	int& ret = cache[width];
	if (ret != -1)
		return ret;
	return ret = (tiling(width - 1) + tiling(width - 2)) % MOD;
}
int main() {
	int C;
	int i, n;
	cin >> C;
	for (i = 0; i < C; i++) {
		memset(cache, -1, sizeof(cache));
		cin >> n;
		cout << tiling(n) << endl;
	}
}