#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
int triangle[100][101],n;
int cache[100][101];
int sum(int x, int y) {
	if (x==n-1)//y->x
		return triangle[x][y];
	int& ret = cache[x][y];
	if (ret != -1)
		return ret;
	return ret = max(sum(x + 1, y), sum(x + 1, y + 1))+triangle[x][y];
}
int main(void) {
	int C;
	int i,j,k;
	cin >> C;
	for (i = 0; i < C; i++) {
		memset(cache, -1, sizeof(cache));
		memset(triangle, 0, sizeof(triangle));
		cin >> n;
		for (j = 0; j < n; j++) {
			for (k = 0; k < j + 1; k++) {
				cin >> triangle[j][k];
			}
		}
		
		cout<<sum(0, 0)<<endl;
	}
}

