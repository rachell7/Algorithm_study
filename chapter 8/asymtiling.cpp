#include <iostream>
#include <cstring>
using namespace std;
const int MOD=1000000007;
int cache[101];
int tiling(int n) {
	if (n <= 1)
		return 1;
	int& ret = cache[n];
	if (ret != -1)
		return ret;
	else
		return ret = (tiling(n - 2) + tiling(n - 1))%MOD;
}
int tile(int n) {
	if (n % 2 == 1)//�汝鶺� 唳辦
		return (tiling(n) - tiling((n - 1) / 2) + MOD) % MOD;
	else//礎熱橾 唳辦
	{
		return (((tiling(n) - tiling(n / 2)+MOD)%MOD) - tiling(n / 2 - 1) + MOD) % MOD; 
	}
}
int main(void) {
	int C;
	int i;
	int n;
	cin >> C;
	memset(cache, -1, sizeof(cache));
	for (i = 0; i < C; i++) {
		cin >> n;
		cout << tile(n) << endl;
	}
}

/*
#include <iostream>
#include <cstring>
using namespace std;
const int MOD = 1000000007;
int cache[101];
int tiling(int n) {
		if (n <= 1)
			return 1;
		int& ret = cache[n];
		if (ret != -1)
			return ret;
		else
			return ret = (tiling(n - 2) + tiling(n - 1))%MOD;
}
int asymmetric(int width) {
	if (width % 2 == 1)
		return (tiling(width) - tiling(width / 2) + MOD) % MOD;
	int ret = tiling(width);
	ret = (ret - tiling(width / 2) + MOD) % MOD;
	ret = (ret - tiling(width / 2 - 1) + MOD) % MOD;
	return ret;
}
int main() {
	int C;
	int n;
	cin >> C;
	memset(cache, -1, sizeof(cache));
	for (int i = 0; i < C; i++) {
		cin >> n;
		cout << asymmetric(n) << endl;
	}
}
*/