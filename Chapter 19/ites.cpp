//my_code
/*
#include <iostream>
#include <queue>
#include <cmath>
using namespace std;

const int MAX_NUM = 50000000;
long long A[MAX_NUM];

int make_count(int N, int K) {
	int i;
	queue <long long> signal;
	long long a = 1983;
	int sum = 0;
	int result = 0;
	for (int i = 0; i < N; i++) {
		long long r = a % 10000 + 1;
		signal.push(r);
		sum += r;
		
		while (sum > K) {
			sum -= signal.front();
			signal.pop();
		}
		if (sum == K)
			result += 1;
		a = (a * 214013 + 2531011) % (long long)pow(2, 32);
	}
	return result;
}

int sum(int N, int K) {
	int i, j;
	long long total = 0;
	int result = 0;
	for (i = 0; i < N; i++) {
		total= 0;
		for (j = i; j < N; j++) {
			total += A[j];
			if (total == K) {
				result += 1;
			}
			else
				break;
		}
	}
	return result;
}

int main() {
	int C;
	int i;
	int K, N;
	cin >> C;
	for (i = 0; i < C; i++) {
		cin >> K >> N;
		cout<<make_count(N,K)<<endl;
	}
}
*/
//ans_code
/*
#include <iostream>
#include <queue>
using namespace std;
struct RNG {
	unsigned seed;
	RNG():seed(1983){}
	unsigned next() {
		unsigned ret = seed;
		seed = ((seed * 214013u) + 2531011u);
		return ret % 10000 + 1;
	}
};
int countRanges(int k, int n) {
	RNG rng;
	queue<int> range;
	int ret = 0, rangeSum = 0;
	for (int i = 0; i < n; i++) {
		int newSignal = rng.next();
		rangeSum += newSignal;
		range.push(newSignal);
		while (rangeSum > k) {
			rangeSum -= range.front();
			range.pop();
		}
		if (rangeSum == k)
			ret++;
	}
	return ret;

}
int main() {
	int C;
	int i;
	int n, k;
	cin >> C;
	for (i = 0; i < C; i++) {
		cin >> k>>n;
		cout << countRanges(k,n) << endl;
	}
}
*/