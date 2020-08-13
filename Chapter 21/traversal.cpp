//my_code
/*
#include <iostream>
#include <vector>
using namespace std;
vector <int> preorder;
vector <int> inorder;
int N;

void postOrder(int pre, int in, int size) {
	int root;
	int i, j;
	if (size < 1)
		return;
	else {
		root = preorder[pre];
		for (i = pre, j = in; i < N; i++, j++) {
			if (root == inorder[j])
				break;
		}
		int lsize = j - in;
		int rsize = (size+in) - (j + 1);
		//l
		postOrder(pre + 1, in, lsize);
		//r
		postOrder(i + 1, j + 1, rsize);
	}
	//R
	cout << root << ' ';
}
int main() {
	int C;
	int i,j,k;
	int num;
	cin >> C;
	for (i = 0; i < C; i++) {
		cin >> N;
		for (j = 0; j < N; j++) {//전위순회
			cin >> num;
			preorder.push_back(num);
		}
		for (k = 0; k < N; k++) {//중위순회
			cin >> num;
			inorder.push_back(num);
		}
		postOrder(0, 0, N);
		cout << "\n";
		preorder.clear();
		inorder.clear();
	}
}
*/
//ans_code

#include<iostream>
#include<vector>
#include <algorithm>
using namespace std;
vector <int> slice(const vector<int>& v, int a, int b) {
	return vector<int>(v.begin() + a, v.begin() + b);
}
void printPostOrder(const vector<int>& preorder, const vector <int>& inorder) {
	const int N = preorder.size();
	if (preorder.empty())
		return;
	const int root = preorder[0];
	const int L = find(inorder.begin(), inorder.end(), root) - inorder.begin();
	const int R = N - 1 - L;
	printPostOrder(slice(preorder, 1, L + 1), slice(inorder, 0, L));
	printPostOrder(slice(preorder, L + 1, N), slice(inorder, L + 1, N));
	cout << root <<' ';
}
int main() {
	int C;
	int N;
	int i, j;
	cin >> C;
	for (i = 0; i < C; i++) {
		cin >> N;
		vector<int> preorder(N);
		vector<int> inorder(N);
		for (j = 0; j < N; j++) {
			cin >> preorder[j];
		}
		for (j = 0; j < N; j++) {
			cin >> inorder[j];
		}
		printPostOrder(preorder, inorder);
		cout << "\n";
	}
}