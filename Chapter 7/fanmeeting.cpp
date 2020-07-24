#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;
string member;
string fan;
/*
int check(string::iterator& ms, string::iterator& fs) {
	string::iterator i, j;
	int size = fan.end() - fs;
	if (size<member.size())
		return 0;
	for (i = ms, j = fs; i != member.end(); i++, j++) {
		
		if (j == fan.end()&&i!=member.end())
			return 0;
		else if (j == fan.end() && i == member.end()) {
			if (*j == 'M' && *i == 'M')
				return 0;
			else
				return 1;
		}
		
		if (*i == 'M' && *j == 'M') {
			return check(ms, ++fs);
		}
	}
	return 1+check(ms,++fs);
}
*/
vector<int> multiply(const vector<int>& a, const vector<int>& b) {
	vector<int> c(a.size() + b.size() + 1, 0);
	for (int i = 0; i < a.size(); i++) {
		for (int j = 0; j < b.size(); j++) {
			c[i + j] += a[i] * b[j];
		}
	}
	//normalize(c);
	return c;
}
//카라츠바의 빠른 정수 곱셈 알고리즘
void addTo(vector<int>& a, const vector<int>& b, int k) {
	for (int i = 0; i < b.size(); i++) {
		a[i + k] += b[i];
	}
}
void subFrom(vector<int>& a, const vector<int>& b) {
	for (int i = 0; i < b.size(); i++) {
		a[i] -= b[i];
	}
}
vector<int> karatsuba(const vector<int>& a, const vector <int>& b) {
	int an = a.size(), bn = b.size();
	if (an < bn)
		return karatsuba(b, a);
	if (an == 0 || bn == 0)
		return vector<int>();
	if (an <= 50)
		return multiply(a, b);
	int half = an / 2;
	vector<int>a0(a.begin(), a.begin() + half);
	vector<int>a1(a.begin() + half, a.end());
	vector<int>b0(b.begin(), b.begin() + min<int>(b.size(), half));
	vector<int>b1(b.begin() + min<int>(b.size(), half), b.end());

	//z2=a1*b1
	vector<int> z2 = karatsuba(a1, b1);
	//z0=z0*b0
	vector<int> z0 = karatsuba(a0, b0);
	//a0=a0+a1
	addTo(a0, a1, 0);
	//b0=b0+b1
	addTo(b0, b1, 0);

	//z1=(a0*b0)-z0-z2
	vector<int>z1 = karatsuba(a0, b0);
	subFrom(z1, z0);
	subFrom(z1, z2);

	//ret=z0+z1*10^half+z2*10^(half*2)
	vector<int> ret;
	addTo(ret, z0, 0);
	addTo(ret, z1, half);
	addTo(ret, z2, half + half);
	return ret;
}

int hugs(const string& members, const string& fans) {
	int N = members.size(), M = fans.size();
	vector<int> A(N), B(M);
	for (int i = 0; i < N; i++) {
		A[i] = (members[i] == 'M');//입력 순서대로
	}
	for (int i = 0; i < M; i++) {
		B[M - i - 1] = (fans[i] == 'M');//거꾸로
	}
	vector<int> C = karatsuba(A, B);

	int allHugs = 0;
	for (int i = N - 1; i < M; i++) {//N-1번째부터 모든 멤버가 팬과 짝을 이룸
		if (C[i] == 0)
			++allHugs;
	}
	return allHugs;
}

int main(void) {
	int C;
	int N, M;
	int i;
	
	cin >> C;
	for (i = 0; i < C; i++) {
		cin >> member;
		cin >> fan;
		string::iterator ms = member.begin();
		string::iterator fs = fan.begin();
		cout << hugs(member,fan)<<endl;
	}

}
