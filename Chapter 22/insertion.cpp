//my_code
#include <iostream>
#include <algorithm>
#include <string.h>
using namespace std;
typedef int KeyType;
struct Node {
	//��忡 ����� ����
	KeyType key;
	//����� �켱����,��带 ��Ʈ�� �ϴ� ����Ʈ���� ũ��
	int priority, size;
	//�� �ڽ� ����� ������
	Node* left, * right;
	//�����ڿ��� ���� �켱������ �����ϰ� size�� left/right�� �ʱ�ȭ
	Node(const KeyType& _key) :key(_key), priority(rand()), size(1), left(NULL), right(NULL) {}
	void setLeft(Node* newLeft) { left = newLeft; calcSize(); }
	void setRight(Node* newRight) { right = newRight; calcSize(); }
	//size��� ����
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
	//������ Ʈ���ΰ��
	if (root == NULL)
		//Ʈ���� ����
		return NodePair(NULL, NULL);
	//root�� key�� node�� key���� ���� ���
	if (root->key < key) {
		//root�� ������ ��Ʈ������ node�� key���� ���� ��쳪 ū ��� ������
		NodePair rs = split(root->right, key);
		//���� Ʈ�� �� node�� key������ ���� Ʈ��(root�� key�����ٴ� ū Ʈ��=>������ Ʈ��)�� ���� root�� ������ Ʈ���� ����
		root->setRight(rs.first);
		//���� ��Ʈ���� root�� ��Ʈ����� ���� �ɰ��� Ʈ���� node�� key���� ū ������ Ʈ���� �̷���� �ΰ��� ��Ʈ�� ��ȯ
		return NodePair(root, rs.second);
	}
	//root�� key�� node�� key���� ū ���
	//root�� key���� ���Ұ��� ���� ���� ��Ʈ���� key���� ���Ͽ� Ʈ�� ����
	NodePair ls = split(root->left, key);
	//���� Ʈ�� �� node�� key������ ū Ʈ��(root�� key�����ٴ� ���� Ʈ��=>���� Ʈ��)�� ���� root�� ���� Ʈ���� ����
	root->setLeft(ls.second);
	//���� ��Ʈ���� root�� ��Ʈ����� ������ Ʈ���� �ɰ��� Ʈ���� node�� key���� ���� ������ Ʈ���� ���� ��Ʈ���� �̷���� �ΰ��� ��Ʈ�� ��ȯ
	return NodePair(ls.first, root);
}
Node* insert(Node* root, Node* node) {
	//������ Ʈ����� ���ο� ��常 ��ȯ
	if (root == NULL)
		return node;
	//root�� �켱�������� node�� �켱������ ���� ���
	if (root->priority < node->priority) {
		//����,������ Ʈ�� ����
		NodePair splitted = split(root, node->key);
		//node�� ��Ʈ�� �ϰ� node���� ���� ���ҵ��� ���� ���� ��Ʈ����
		node->setLeft(splitted.first);
		//node���� ū ���ҵ��� ���� ������ ��Ʈ���� node�� �մ´�
		node->setRight(splitted.second);
		//�̾��� node�� ��Ʈ�� ��ȯ
		return node;
	}
	//root�� �켱�������� node�� �켱������ ���� ���
	//root�� ����,������ ��Ʈ���� ��Ʈ���� ���ϸ� ����
	//node�� key�� root�� key���� ���� ���
	else if (node->key < root->key) {
		//���� ��Ʈ���� �̵�
		root->setLeft(insert(root->left, node));
	}
	//node�� key�� root�� key���� ū ���
	else {
		//������ ��Ʈ���� �̵�
		root->setRight(insert(root->right, node));
	}
	//���� root��ȯ
	return root;
}
Node* kth(Node* root, int k) {
	//���� ����Ʈ���� ũ�� ���
	int leftSize = 0;
	if (root->left != NULL)
		leftSize = root->left->size;
	//k�� ���� ����Ʈ�� ���ο� ���� ���
	if (k <= leftSize)
		//���� ����Ʈ���� �� ��ȸ
		return kth(root->left, k);
	//���� Ʈ���� ������� ���� ��Ʈ���� ���ļ� k��
	if (k == leftSize + 1)
		//���� root�� ��ȯ
		return root;
	//k�� ������ ����Ʈ���� ���� ��
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