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
	//¦�� �������� ���� ���� ���� ��ȣ �л�
	if (first == -1) {
		return 1;
	}
	//��� �л��� ¦�� ������
	for (int j = first+1; j < n; j++) {
		if (!Pair[j] && Friend[first][j]) {
			Pair[first] = Pair[j] = true;
			sum += count(n, Pair);//�տ��� ��Ī�ϰ�
			Pair[first] = Pair[j] = false;//�ڿ������� ���� 
		}
	}
	return sum;
}

int main() {
	int i,j;
	int a, b;
	int C;//C:�׽�Ʈ ���̽�
	int n, m;//n:�л��� �� �ο�, m:ģ�� ���� ��
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