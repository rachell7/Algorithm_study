#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;
vector<int> s;
int N;
int cache[500];

/*
int subsequence(int index) {
	vector<int> ss;
	ss.push_back(s[index]);
	for (int i = index+1; i < N; i++) {
		if (ss.back() < s[i])
			ss.push_back(s[i]);
	}
	return ss.size();
}
int max_length() {
	int m = 0;
	int i;
	for (i = 0; i < N; i++) {
		m = max(m, subsequence(i));
	}
	return m;
}
*/

int subsequence(int index) {
	vector<int> ss;
	ss.push_back(s[index]);
	int& ret = cache[index];
	if (ret != -1)
		return ret;
	ret = 1;
	for (int i = index+1; i < N; i++) {
		if (s[index] < s[i])
			ret = max(ret, 1+subsequence(i));
	}
	return ret;
}
int max() {
	int m = 0;
	for (int i = 0; i < N; i++) {
		m=max(m,subsequence(i));
	}
	return m;
}
int main(void) {
	int C;
	int i,j;
	int num;
	cin >> C;
	for (i = 0; i < C; i++) {
		memset(cache, -1, sizeof(cache));
		cin >> N;
		for (j = 0; j < N; j++) {
			cin >> num;
			s.push_back(num);
		}
		cout << max() << endl;
		s.clear();
	}
}