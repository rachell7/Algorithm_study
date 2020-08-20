//my_code
#include <iostream>
#include <algorithm>
#include <string.h>
using namespace std;
typedef int KeyType;
struct Node {
	//노드에 저장된 원소
	KeyType key;
	//노드의 우선순위,노드를 루트로 하는 서브트리의 크기
	int priority, size;
	//두 자식 노드의 포인터
	Node* left, * right;
	//생성자에서 난수 우선순위를 생성하고 size와 left/right를 초기화
	Node(const KeyType& _key) :key(_key), priority(rand()), size(1), left(NULL), right(NULL) {}
	void setLeft(Node* newLeft) { left = newLeft; calcSize(); }
	void setRight(Node* newRight) { right = newRight; calcSize(); }
	//size멤버 갱신
	void calcSize() {
		size = 1;
		if (left)
			size += left->size;
		if (right)
			size += right->size;
	}
};
typedef pair<Node*, Node*> NodePair;
NodePair split(Node* root, KeyType key) {
	//공백의 트리인경우
	if (root == NULL)
		//트리가 없음
		return NodePair(NULL, NULL);
	//root의 key가 node의 key보다 작은 경우
	if (root->key < key) {
		//root의 오른쪽 부트리에서 node의 key보다 작은 경우나 큰 경우 나누기
		NodePair rs = split(root->right, key);
		//나눈 트리 중 node의 key값보다 작은 트리(root의 key값보다는 큰 트리=>오른쪽 트리)를 현재 root의 오른쪽 트리로 설정
		root->setRight(rs.first);
		//현재 부트리는 root가 루트노드인 경우와 쪼개진 트리의 node의 key보다 큰 원소의 트리로 이루어진 두개의 부트리 반환
		return NodePair(root, rs.second);
	}
	//root의 key가 node의 key보다 큰 경우
	//root의 key보다 원소값이 작은 왼쪽 부트리를 key값과 비교하여 트리 생성
	NodePair ls = split(root->left, key);
	//나눈 트리 중 node의 key값보다 큰 트리(root의 key값보다는 작은 트리=>왼쪽 트리)를 현재 root의 왼쪽 트리로 설정
	root->setLeft(ls.second);
	//현재 부트리는 root가 루트노드인 오른쪽 트리와 쪼개진 트리의 node의 key보다 작은 원소의 트리인 왼쪽 부트리로 이루어진 두개의 부트리 반환
	return NodePair(ls.first, root);
}
Node* insert(Node* root, Node* node) {
	//공백의 트리라면 새로운 노드만 반환
	if (root == NULL)
		return node;
	//root의 우선순위보다 node의 우선순위가 높은 경우
	if (root->priority < node->priority) {
		//왼쪽,오른쪽 트리 생성
		NodePair splitted = split(root, node->key);
		//node를 루트로 하고 node보다 작은 원소들이 모인 왼쪽 부트리와
		node->setLeft(splitted.first);
		//node보다 큰 원소들이 모인 오른쪽 부트리를 node에 잇는다
		node->setRight(splitted.second);
		//이어진 node를 루트로 반환
		return node;
	}
	//root의 우선순위보다 node의 우선순위가 작은 경우
	//root의 왼쪽,오른쪽 부트리의 루트노드와 비교하며 진행
	//node의 key가 root의 key보다 작은 경우
	else if (node->key < root->key) {
		//왼쪽 부트리로 이동
		root->setLeft(insert(root->left, node));
	}
	//node의 key가 root의 key보다 큰 경우
	else {
		//오른쪽 부트리로 이동
		root->setRight(insert(root->right, node));
	}
	//현재 root반환
	return root;
}
Node* kth(Node* root, int k) {
	//왼쪽 서브트리의 크기 계산
	int leftSize = 0;
	if (root->left != NULL)
		leftSize = root->left->size;
	//k가 왼쪽 서브트리 내부에 있을 경우
	if (k <= leftSize)
		//왼쪽 서브트리로 들어가 순회
		return kth(root->left, k);
	//왼쪽 트리의 사이즈와 현재 루트까지 합쳐서 k개
	if (k == leftSize + 1)
		//현재 root값 반환
		return root;
	//k가 오른쪽 서브트리에 있을 때
	return kth(root->right, k - leftSize - 1);
}
Node* merge(Node* a, Node* b) {
	if (a == NULL)
		return b;
	if (b == NULL)
		return a;
	if (a->priority < b->priority) {
		b->setLeft(merge(a, b->left));
		return b;
	}
	a->setRight(merge(a->right, b));
	return a;
}
Node* erase(Node* root, KeyType key) {
	if (root == NULL)
		return root;
	if (root->key == key) {
		Node* ret = merge(root->left, root->right);
		delete root;
		return ret;
	}
	if (key < root->key) {
		root->setLeft(erase(root->left, key));
	}
	else {
		root->setRight(erase(root->right, key));
	}
	return root;
}
/*
int movement[50000];
void reverse_insert(int N) {
	int original[50000];
	Node* root=NULL;
	for (int i = 1; i <= N; i++) {
		root = insert(root, new Node(i));
	}
	for (int i = N - 1; i >= 0; i--) {
		int l = movement[i];
		original[i] = kth(root, i + 1 - l)->key;
		root = erase(root, original[i]);
	}
	for (int i = 0; i < N; i++) {
		cout << original[i] << ' ';
	}
}
int main(void) {
	int C;
	int N;
	cin >> C;
	for (int i = 0; i < C; i++) {
		cin >> N;
		for (int j = 0; j < N; j++) {
			cin >> movement[j];
		}
		reverse_insert(N);
		memset(movement, 0, sizeof(int)*N);
	}
}
*/
int n, shifted[50000];
int A[50000];
void solve() {
	Node* candidates = NULL;
	for (int i = 0; i < n; i++) {
		candidates = insert(candidates, new Node(i + 1));
	}
	for (int i = n - 1; i >= 0; i--) {
		int larger = shifted[i];
		Node* k = kth(candidates, i + 1 - larger);
		A[i] = k->key;
		candidates = erase(candidates, k->key);
	}
}
int main() {
	int C;
	cin >> C;
	for (int i = 0; i < C; i++) {
		cin >> n;
		for (int j = 0; j < n; j++) {
			cin >> shifted[j];
		}
		solve();
		for(int i=0;i<n;i++){
			cout << A[i] << ' ';
		}
		cout << endl;
		memset(shifted, 0, sizeof(int) * n);
		memset(A, 0, sizeof(int) * n);
	}
}