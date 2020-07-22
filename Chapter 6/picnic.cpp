#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
using namespace std;
bool Friend[10][10];
bool Pair[10];
int count(int n,bool Pair[]) {
	int i, j;
	int first = -1;
	int sum = 0;
	for (i = 0; i < n; i++) {
		if (!Pair[i]) {
			first = i;
			break;
		}
	}
	//짝이 지어지지 않은 가장 빠른 번호 학생
	if (first == -1) {
		return 1;
	}
	//모든 학생이 짝이 지어짐
	for (int j = first+1; j < n; j++) {
		if (!Pair[j] && Friend[first][j]) {
			Pair[first] = Pair[j] = true;
			sum += count(n, Pair);//앞에서 매칭하고
			Pair[first] = Pair[j] = false;//뒤에서부터 해제 
		}
	}
	return sum;
}

int main() {
	int i,j;
	int a, b;
	int C;//C:테스트 케이스
	int n, m;//n:학생의 총 인원, m:친구 쌍의 수
	cin >> C;
	for (i = 0; i < C; i++) {
		cin >> n>>m;
		for (j = 0; j < m; j++) {
			cin >> a >> b;
			Friend[a][b] = true;
			Friend[b][a] = true;
		}
		cout << count(n, Pair)<<endl;
		memset(Friend, false, sizeof(Friend));
	}
	
}