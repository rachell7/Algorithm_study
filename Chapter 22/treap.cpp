#include <iostream>
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
	Node(const KeyType& _key):key(_key),priority(rand()),size(1),left(NULL),right(NULL){}
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
//노드의 추가와 쪼개기 연산
typedef pair<Node*, Node*> NodePair;
// root를 루트로 하는 트립을 key미만의 값과 이상의 값을 두 개의 트립으로 분리
//전제: 우선순위는 node가 root보다 높음
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
//root를 루트로 하는 트립에 새 노드 node를 삽입한 뒤 결과 트립의 루트를 반환
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
		root->setLeft(insert(root->left,node));
	}
	//node의 key가 root의 key보다 큰 경우
	else {
		//오른쪽 부트리로 이동
		root->setRight(insert(root->right, node));
	}
	//현재 root반환
	return root;
}
//노드의 삭제와 합치기 연산
//전제: max(a) < min(b) 이다
Node* merge(Node* a, Node* b) {
	//a가 없을 때 b만 반환
	if (a == NULL)
		return b;
	//b가 없을 때 a만 반환
	if (b == NULL)
		return a;
	//a의 우선순위 < b의 우선순위
	if (a->priority < b->priority) {
		//b의 왼쪽 트리와 a를 병합하여 b의 왼쪽 부트리로 생성
		b->setLeft(merge(a, b->left));
		//루트노드인 b를 반환
		return b;
	}
	//a의 우선순위 > b의 우선순위
	//a의 오른쪽 부트리와 b를 병합하여 a의 오른쪽 부트리로 생성
	a->setRight(merge(a->right, b));
	//루트노드인 a를 반환
	return a;
}
//root를 루트로 하는 트립에서 key를 지우고 결과 트립의 루트를 반환
Node* erase(Node* root, KeyType key) {
	//공백 트리이면 그대로 반환
	if (root == NULL)
		return root;
	//root의 key가 key이면
	if (root->key == key) {
		//루트 노드를 제외한 두 개의 부트리를 병합
		Node* ret = merge(root->left, root->right);
		//루트 노드를 삭제
		delete root;
		//새로운 루트노드 반환
		return ret;
	}
	//key가 현재 root의 key보다 작으면
	if (key < root->key) {
		//root의 왼쪽트리에서 찾아보기
		root->setLeft(erase(root->left, key));
	}
	//key가 현재 root의 key보다 크면
	else {
		//root의 오른쪽트리에서 찾아보기
		root->setRight(erase(root->right, key));
	}
	//현재 root반화
	return root;
}
//k번째 원소 찾기
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
//X보다 작은 원소 세기
int countLessThan(Node* root, KeyType key) {
	//빈 트리일 때
	if (root == NULL)
		return 0;
	//key보다 큰 경우
	if (root->key >= key)
	//현재 노드보다 작은 원소들이 속한 왼쪽 부트리를 확인
		return countLessThan(root->left, key);
	//해당 노드의 왼쪽부트리는 무조건 노드보다 작으므로 왼쪽트리의 노드수
	int ls = (root->left ? root->left->size : 0);
	//왼쪽 부트리의 노드수와 현재 루트, 그리고 오른쪽 부트리도 확인
	return ls + 1 + countLessThan(root->right, key);
}
