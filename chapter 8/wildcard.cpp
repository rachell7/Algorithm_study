#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
string W;
string file[50];//파일명
int n;
int flag = 0;

bool compare(string s1, string s2) {
	return s1 < s2;
}
bool same(int index,int w_start, int f_start) {
	int i, j;
	for (i = w_start,j=f_start; i < W.length(); i++,j++) {
		if (W[i]==file[index][j]||W[i]=='?'&&j<file[index].size()) {
			continue;
		}
		if(W[i] == '*') {
			flag = 1;
			for (int next = 0; next + j <= file[index].size();next++) {
				if (same(index, i + 1, j + next)) {
					return true;
				}
			}
		}
	}
	if (flag == 0)
		return W.size() == file[index].size();
	return false;
}

bool same1(const string&w, const string&s) {
	int pos = 0;
	while (pos < w.size() && pos < s.size() && (w[pos] == '?' || w[pos] == s[pos]))
		++pos;
	if (pos == w.size())
		return pos == s.size();
	if (w[pos] == '*') {
		for (int skip = 0; pos + skip <= s.size(); skip++) {
			if (same1(w.substr(pos + 1), s.substr(pos + skip)))
				return true;
		}
	}
	return false;
}

void print_name1() {
	int i;
	sort(file, file + n, compare);
	
	for (i = 0; i < n; i++) {
		if (same1(W, file[i]))
			cout << file[i] << endl;
	}
}

void print_name() {
	int i;
	sort(file, file + n, compare);

	for (i = 0; i < n; i++) {
		flag = 0;
		if (same(i,0,0))
			cout << file[i] << endl;
	}
}

int main(void) {
	int C;
	int i,j;
	cin >> C;//테스트케이스
	for (i = 0; i < C; i++) {
		cin >> W;//와일드카트 패턴
		cin >> n;//파일명의 수
		for (j = 0; j < n; j++) {
			cin >> file[j];//파일이름
		}
		print_name();
		file->clear();
	}
}
