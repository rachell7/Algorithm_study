//#include <iostream>
//#include <list>
//#include <algorithm>
//using namespace std;
//list <int> p;
//int N, K;
//void suicide() {
//	int i;
//	list <int>::iterator it;
//	for (i = 0; i < N; i++) {
//		p.push_back(i + 1);
//	}
//
//	it = p.begin();
//	while (p.size() != 2) {
//		it=p.erase(it);
//		
//		for (i = 0; i < K-1; i++) {
//			if (it == p.end()) {
//				it = p.begin();
//			}
//			it++;
//		}
//
//		if (it == p.end()) {
//			it = p.begin();
//		}
//	}
//	it = p.begin();
//	cout << *(it) << " ";
//	cout<< *(++it) << endl;
//	
//}
//int main(void) {
//	int C;
//	int i;
//	cin >> C;
//	for (i = 0; i < C; i++) {
//		cin >> N >> K;//N¸í K¹øÂ°
//		suicide();
//		p.clear();
//	}
//}

#include <iostream>
#include <list>
using namespace std;
void josephus(int n, int k) {
	list<int> survivors;
	for (int i = 1; i <= n; i++) {
		survivors.push_back(i);
	}
	list<int>::iterator kill = survivors.begin();
	while (n > 2) {
		kill = survivors.erase(kill);
		if (kill == survivors.end())
			kill = survivors.begin();
		--n;
		for (int i = 0; i < k - 1; i++) {
			++kill;
			if (kill == survivors.end())
				kill = survivors.begin();
		}
	}
	cout << survivors.front() << " " << survivors.back() << endl;
}
int main() {
	int C;
	int N, K;
	cin >> C;
	for (int i = 0; i < C; i++) {
		cin >> N >> K;
		josephus(N, K);
	}
}