
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#define MAX_SIZE 20000
using namespace std;
string original;
//���� ���ڿ� �����ϱ�
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

//���� �� Ǯ�� �ʰ� ������
string reverse(string::iterator& it) {
	char head = *it;//ù��° �� x�ϰ��
	++it;
	if (head == 'b' || head == 'w')
		return string(1, head);
	string upperLeft = reverse(it);//���� ��
	string upperRight = reverse(it);//������ ��
	string lowerLeft = reverse(it);//���� �Ʒ�
	string lowerRight = reverse(it);//������ �Ʒ�
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
