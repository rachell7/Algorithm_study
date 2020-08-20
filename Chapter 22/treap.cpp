#include <iostream>
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
	Node(const KeyType& _key):key(_key),priority(rand()),size(1),left(NULL),right(NULL){}
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
//����� �߰��� �ɰ��� ����
typedef pair<Node*, Node*> NodePair;
// root�� ��Ʈ�� �ϴ� Ʈ���� key�̸��� ���� �̻��� ���� �� ���� Ʈ������ �и�
//����: �켱������ node�� root���� ����
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
//root�� ��Ʈ�� �ϴ� Ʈ���� �� ��� node�� ������ �� ��� Ʈ���� ��Ʈ�� ��ȯ
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
		root->setLeft(insert(root->left,node));
	}
	//node�� key�� root�� key���� ū ���
	else {
		//������ ��Ʈ���� �̵�
		root->setRight(insert(root->right, node));
	}
	//���� root��ȯ
	return root;
}
//����� ������ ��ġ�� ����
//����: max(a) < min(b) �̴�
Node* merge(Node* a, Node* b) {
	//a�� ���� �� b�� ��ȯ
	if (a == NULL)
		return b;
	//b�� ���� �� a�� ��ȯ
	if (b == NULL)
		return a;
	//a�� �켱���� < b�� �켱����
	if (a->priority < b->priority) {
		//b�� ���� Ʈ���� a�� �����Ͽ� b�� ���� ��Ʈ���� ����
		b->setLeft(merge(a, b->left));
		//��Ʈ����� b�� ��ȯ
		return b;
	}
	//a�� �켱���� > b�� �켱����
	//a�� ������ ��Ʈ���� b�� �����Ͽ� a�� ������ ��Ʈ���� ����
	a->setRight(merge(a->right, b));
	//��Ʈ����� a�� ��ȯ
	return a;
}
//root�� ��Ʈ�� �ϴ� Ʈ������ key�� ����� ��� Ʈ���� ��Ʈ�� ��ȯ
Node* erase(Node* root, KeyType key) {
	//���� Ʈ���̸� �״�� ��ȯ
	if (root == NULL)
		return root;
	//root�� key�� key�̸�
	if (root->key == key) {
		//��Ʈ ��带 ������ �� ���� ��Ʈ���� ����
		Node* ret = merge(root->left, root->right);
		//��Ʈ ��带 ����
		delete root;
		//���ο� ��Ʈ��� ��ȯ
		return ret;
	}
	//key�� ���� root�� key���� ������
	if (key < root->key) {
		//root�� ����Ʈ������ ã�ƺ���
		root->setLeft(erase(root->left, key));
	}
	//key�� ���� root�� key���� ũ��
	else {
		//root�� ������Ʈ������ ã�ƺ���
		root->setRight(erase(root->right, key));
	}
	//���� root��ȭ
	return root;
}
//k��° ���� ã��
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
//X���� ���� ���� ����
int countLessThan(Node* root, KeyType key) {
	//�� Ʈ���� ��
	if (root == NULL)
		return 0;
	//key���� ū ���
	if (root->key >= key)
	//���� ��庸�� ���� ���ҵ��� ���� ���� ��Ʈ���� Ȯ��
		return countLessThan(root->left, key);
	//�ش� ����� ���ʺ�Ʈ���� ������ ��庸�� �����Ƿ� ����Ʈ���� ����
	int ls = (root->left ? root->left->size : 0);
	//���� ��Ʈ���� ������ ���� ��Ʈ, �׸��� ������ ��Ʈ���� Ȯ��
	return ls + 1 + countLessThan(root->right, key);
}
