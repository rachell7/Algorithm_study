//my_code
/*
#include <iostream>
#include <set>
#include <map>
#pragma warning(disable:4996)
using namespace std;
map<int, int>m;
int in_possible(int p, int q) {
	if (m.empty()) {
		m.insert(pair<int, int>(p, q));
		return 1;
	}
	map<int, int>::iterator iter;
	for (iter = m.begin(); iter != m.end(); ) {
		if ((*iter).first < p && (*iter).second < q) {
			m.erase(iter++);
		}
		else {
			++iter;
		}
	}
	m.insert(pair<int, int>(p, q));
	return m.size();
}
int main(void) {
	int C;
	int i,j;
	int N;
	int p, q;
	int total = 0;
	cin >> C;
	for (i = 0; i < C; i++) {
		scanf("%d", &N);
		total = 0;
		for (j = 0; j < N; j++) {
			scanf("%d %d", &p, &q);
			total+=in_possible(p, q);
		}
		printf("%d\n",total);
		m.clear();
	}	
}
*/
//ans_code
/*
#include <iostream>
#include <algorithm>
#include <map>
using namespace std;
map<int, int> coords;

//지배 당하는지 여부
bool isDominated(int x, int y) {
	map<int, int>::iterator it = coords.lower_bound(x);//x이상의 키 중 가장 작은 값
	//그런 점이 없으면 지배당하지 않는다
	if (it == coords.end())
		return false;
	return y < it->second;
}
void removeDominated(int x, int y) {
	map<int, int>::iterator it = coords.lower_bound(x);
	if (it == coords.begin())
		return;
	--it;
	while (true) {
		if (it->second > y)
			break;
		if (it == coords.begin()) {
			coords.erase(it);
			break;
		}
		else {
			map<int, int>::iterator jt = it;
			--jt;
			coords.erase(it);
			it = jt;
		}
	}
}
int registered(int x, int y) {
	if (isDominated(x, y))
		return coords.size();
	removeDominated(x, y);
	coords[x] = y;
	return coords.size();
}
int main(void) {
	int C;
	int i,j;
	int N;
	int p, q;
	int sum = 0;
	cin >> C;
	for (i = 0; i < C; i++) {
		cin >> N;
		sum = 0;
		for (j = 0; j < N; j++) {
			cin >> p >> q;
			sum+=registered(p, q);
		}
		cout << sum << endl;
		coords.clear();
	}
}
*/