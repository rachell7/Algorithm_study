
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#define MAX_SIZE 20000
using namespace std;
string original;
//압축 문자열 분할하기
char decompressed[MAX_SIZE][MAX_SIZE];
void decompress(string::iterator& it, int y, int x, int size) {
	char head = *(it++);
	if (head == 'b' || head == 'w') {
		for (int dy = 0; dy < size; dy++) {
			for (int dx = 0; dx < size; dx++) {
				decompressed[y + dy][x + dx] = head;
			}
		}
	}
	else {
		int half = size / 2;
		decompress(it, y, x, half);
		decompress(it, y, x+half, half);
		decompress(it, y+half, x, half);
		decompress(it, y+half, x+half, half);
	}
}

//압축 다 풀지 않고 뒤집기
string reverse(string::iterator& it) {
	char head = *it;//첫번째 값 x일경우
	++it;
	if (head == 'b' || head == 'w')
		return string(1, head);
	string upperLeft = reverse(it);//왼쪽 위
	string upperRight = reverse(it);//오른쪽 위
	string lowerLeft = reverse(it);//왼쪽 아래
	string lowerRight = reverse(it);//오른쪽 아래
	return string("x") + lowerLeft + lowerRight + upperLeft + upperRight;
}

int main(void) {
	int C;
	cin >> C;

	for (int i = 0; i < C; i++) {
		cin >> original;
		string::iterator itr = original.begin();
		cout<<reverse(itr)<<endl;
	}
}
