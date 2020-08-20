//my code 
/*
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
vector <long long> heap;
long long median(vector<long long>& heap) {
	long long m = heap.size();
	if (m % 2 == 0) {
		long long r = m / 2 - 1;
		long long l = m / 2;
		if (heap[r] < heap[l])
			return heap[r];
		else
			return heap[l];
	}
	else {
		m = m / 2;
		return heap[m];
	}
}
long long newValue(long long N,long long a, long long b) {
	long long sum = 0;
	long long start = 1983;
	for (long long i = 0; i < N; i++) {
		if (i == 0)
			heap.push_back(start);
		else {
			start = (a*start+b)%20090711;
			heap.push_back(start);
		}
		sort(heap.begin(), heap.end());
		sum += median(heap);
	}
	return sum % 20090711;
}
int main(void) {
	int C;
	int i;
	long long N,a,b;
	cin >> C;
	for (i = 0; i < C; i++) {
		cin >> N >> a >> b;
		cout << newValue(N, a, b)<< endl;
		heap.clear();
	}
}
*/
//ans_code
#include <iostream>
#include <vector>
#include <queue>
#include <functional>
#include <algorithm>
using namespace std;

struct RNG {
	int seed, a, b;
	RNG(int _a, int _b):a(_a),b(_b),seed(1983){}
	int next() {
		int ret = seed;
		seed = ((seed * (long long)a) + b) % 20090711;
		return ret;
	}
};
int runningMedian(int n, RNG rng) {
	priority_queue<int, vector<int>, less<int>> maxHeap;
	priority_queue<int, vector<int>, greater<int>> minHeap;
	int ret = 0;
	//최대 힙의 크기는 최소 힙의 크기와 같거나, 하나 더 크다.
	//최대 힙의 최대 원소는 최소 힙의 최소 원소보다 작거나 같다
	for (int cnt = 1; cnt <= n; cnt++) {
		if (maxHeap.size() == minHeap.size())
			maxHeap.push(rng.next());
		else
			minHeap.push(rng.next());
		if (!minHeap.empty() && !maxHeap.empty() && minHeap.top() < maxHeap.top()) {
			int a = maxHeap.top(), b = minHeap.top();
			maxHeap.pop();
			minHeap.pop();
			maxHeap.push(b);
			minHeap.push(a);
		}
		ret = (ret + maxHeap.top()) % 20090711;
	}
	return ret;
}

int main(void) {
	int C;
	int N, a, b;
	cin >> C;
	for (int i = 0; i < C; i++) {
		cin >> N >> a >> b;
		RNG rng(a, b);
		cout << runningMedian(N, rng) << endl;
	}
}

